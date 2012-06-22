#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include "tcpreciever.h"
#include "board.h"
#include "chessboard.h"
#include "ui_mainwindow.h"
#include "netplayer.h"

class Client : public QObject
{
    Q_OBJECT
public:
    Client( Ui::MainWindow *ui);
    Client(QString ipAddress,Ui::MainWindow *ui, Player *guest);
public:
    void connectToServer(QString clientName);
    void invite(QString rivalName);
private slots:
    void readMessage();

private:
    void join();
    Ui::MainWindow *ui;
    QTcpSocket *tcpSocket;
    Player *guest;
};

#endif // CLIENT_H
