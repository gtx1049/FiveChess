#include "server.h"

#include <iostream>
using namespace std;
Server::Server()
{
    tcpServer = new QTcpServer();
    if(!tcpServer->listen(QHostAddress::LocalHost,NETNUMBER))
    { //监听本地主机的PORTNUMBER端口，如果出错就输出错误信息，并关闭
        qDebug() << tcpServer->errorString();
        tcpServer->close();
    }
    connect(tcpServer,SIGNAL(newConnection()),this,SLOT(welcome()));

}

void Server::welcome()
{
    availabe = true;
    tcpSocket = tcpServer->nextPendingConnection();

//    for(int i = 0 ,j = tcpSockets.size(); i < j; i++)
//    {
//        if(tcpSockets[i]->peerAddress() == tcpSocket->peerAddress())
//        {
//            availabe = false;
//            return;
//        }
//    }

    connect(tcpSocket,SIGNAL(readyRead()),this,SLOT(readMessage()));
}

void Server::readMessage()
{
    for(int i = 0, j = tcpSockets.size(); i < j; i++)
    {
        if(tcpSockets[i]->isReadable() && tcpSockets[i]->bytesAvailable())
        {
            cout<<i<<endl;
            tcpSocket = tcpSockets[i];

        }
    }

    Message message;
    TcpReciever *tcpReciever = new TcpReciever(tcpSocket);
    tcpReciever->recieveStep(message);

    switch(message.status)
    {

    case CONNECT:
    {
        if(!availabe)
        {
            //此ip已登陆过
            return;
        }

        QString clientName = message.clientName;

        //检测是否重名，若是则现实提示，用户重新输入
        for(int i = 0,j = playerNames.size(); i < j; i++)
        {
            if(playerNames[i] == clientName)
            {
                return;
            }
        }

        Message _message;
        _message.status = LIST;

        tcpSocket->setObjectName(clientName);
        playerNames.push_back(clientName);

        tcpSockets.push_back(tcpSocket);
        _message.playerNames = playerNames;

        for(int i = 0, j=tcpSockets.size();i < j;i++){
            tcpSocket = tcpSockets[i];
            TcpSender *tcpSender = new TcpSender(tcpSocket);

            for(int m = 0, n = playerNames.size(); m < n; m++)
            {
                if(playerNames[m] == tcpSocket->objectName())
                {
                    _message.playerNames.remove(m);
                }
            }
            tcpSender->sendStep(_message);
            _message.playerNames = playerNames;
        }

        cout<<"new connection is coming"<<endl;
        cout<<clientName.toAscii().data()<<endl;

        break;
    }
    case JOIN:
    {
        QString rivalName = message.rivalName;
        QString ipAddress = tcpSocket->peerAddress().toString();

        //要找的对手以断开链接，给用户提示
        tcpSocket = tcpServer->findChild<QTcpSocket*>(rivalName);
//        if(tcpSocket == 0)
//        {
//            return;
//        }

        Message _message;
        _message.status = JOIN;
        _message.ipAddress = ipAddress;

        TcpSender *tcpSender = new TcpSender(tcpSocket);
        tcpSender->sendStep(_message);

    }
        break;
    }
}
