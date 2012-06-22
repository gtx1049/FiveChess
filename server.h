#ifndef SERVER_H
#define SERVER_H

#include <QObject>
#include "tcpreciever.h"
#include "chessboard.h"
#include "board.h"
#include "ui_mainwindow.h"
#include "netplayer.h"
class Server : public QObject
{
    Q_OBJECT
public:
    Server(Ui::MainWindow *ui,Player *guest);
private slots:
    void readMessage();
    void welcome();

private:
    QObject *object;
    QTcpServer *tcpServer;
    QTcpSocket *tcpSocket;
    //TcpReciever *tcpReciever;

    Player *guest;
    Ui::MainWindow *ui;
};

#endif // SERVER_H
