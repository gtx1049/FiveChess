#include "server.h"
#include <iostream>
using namespace std;
Server::Server(Ui::MainWindow *ui, Player *guest)
{
    this->ui = ui;
    this->guest = guest;
    tcpServer = new QTcpServer();
    if(!tcpServer->listen(QHostAddress::LocalHost,HOSTNUMBER))
    { //监听本地主机的PORTNUMBER端口，如果出错就输出错误信息，并关闭
        qDebug() << tcpServer->errorString();
        tcpServer->close();
    }
    connect(tcpServer,SIGNAL(newConnection()),this,SLOT(welcome()));

}

void Server::welcome()
{

    ui->hostChose->hide();
    ui->playScreen->show();

    tcpSocket = tcpServer->nextPendingConnection();
    connect(tcpSocket,SIGNAL(readyRead()),this,SLOT(readMessage()));
    ui->playScreen->acceptTcp(tcpSocket);
    //cout<<tcpSocket->ipAddress.toAscii().data()<<endl;
}

void Server::readMessage()
{
    Message message;
    TcpReciever *tcpReciever = new TcpReciever(tcpSocket);
    tcpReciever->recieveStep(message);

    switch(message.status)
    {
    case CONNECT:
//        ui->hostChose->hide();
//        ui->playScreen->show();
//        ui->playScreen->setGameMode(NET_MUTI);
        break;
    case JOIN:
//        message.rivalName;
        break;
    case DOWN:
    {
        ChessBoard *maincb = ui->playScreen->getChessBoard();
        guest->doAct(ChessPos(message.point.x,message.point.y), maincb);
        ui->playScreen->repaint();
        ui->playScreen->getNetPlayer()->setActive(true);
        break;
    }
    case UNDO:
        break;
    }
}
