#include "client.h"
#include "board.h"
#include "player.h"
#include <iostream>
using namespace std;
Client::Client(Ui::MainWindow *ui)
{
    this->ui = ui;
    tcpSocket = new QTcpSocket();

    connect(tcpSocket,SIGNAL(readyRead()),this,SLOT(readMessage()));
    tcpSocket->abort();
    tcpSocket->connectToHost(NETIP,NETNUMBER);
}

Client::Client(QString ipAddress,Ui::MainWindow *ui, Player *guest)
{
    this->ui = ui;
    this->guest = guest;
    tcpSocket = new QTcpSocket();

    connect(tcpSocket,SIGNAL(readyRead()),this,SLOT(readMessage()));
    tcpSocket->abort();
    tcpSocket->connectToHost(ipAddress,HOSTNUMBER);
    ui->playScreen->acceptTcp(tcpSocket);

    ui->hostChose->hide();
    ui->playScreen->show();
    ui->playScreen->acceptTcp(tcpSocket);

    ui->playScreen->getNetPlayer()->setChesstype(WHITE_CHESS);
    ui->playScreen->getNetPlayer()->setActive(false);
}

void Client::connectToServer(QString clientName)
{
    Message message;
    message.status = CONNECT;
    message.clientName = clientName;
    TcpSender *tcpSender = new TcpSender(tcpSocket);
    tcpSender->sendStep(message);
}

void Client::join()
{


}



void Client::readMessage()
{

    Message message;
    TcpReciever *tcpReciever = new TcpReciever(tcpSocket);
    tcpReciever->recieveStep(message);
    QVector<QString> playerNames;
    switch(message.status)
    {
    case CONNECT:

    case JOIN:
    {

        cout<<message.ipAddress.toAscii().data()<<endl;
        Player *guest = new NetPlayer(BLACK_CHESS);
        //Client *cliten = new Client(message.ipAddress,ui,guest);
        new Client(message.ipAddress,ui,guest);//危险，没有释放内存
    }
        break;
    case DOWN:
    {
        ChessBoard *maincb = ui->playScreen->getChessBoard();
        Chess lastChess = guest->doAct(ChessPos(message.point.x,message.point.y), maincb);
        if(maincb->judgeVictory(lastChess))
        {
            QMessageBox::about(NULL, "xx", "You Lose!");
        }
        ui->playScreen->repaint();
        ui->playScreen->getNetPlayer()->setActive(true);
        break;
    }
    case UNDO:
        break;
    case LIST:
    {
        ui->rivalName->clear();
        playerNames = message.playerNames;
        for(int i = 0; i < playerNames.size(); i++)
            ui->rivalName->addItem(playerNames[i]);
        ui->rivalName->show();
    }
    }
}

void Client::invite(QString rivalName)
{
    Message message;
    message.status = JOIN;
    message.rivalName = rivalName;
    TcpSender *tcpSender = new TcpSender(tcpSocket);
    tcpSender->sendStep(message);
}
