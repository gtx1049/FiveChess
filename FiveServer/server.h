#ifndef SERVER_H
#define SERVER_H

#include <QObject>
#include "tcpreciever.h"
#include <QVector>

class Server : public QObject
{
    Q_OBJECT
public:
    Server();
private slots:
    void readMessage();
    void welcome();

private:
    QObject *object;
    QTcpServer *tcpServer;
    QTcpSocket *tcpSocket;

    QVector<QTcpSocket *> tcpSockets;
    QVector<QString> playerNames;
    bool availabe;
};

#endif // SERVER_H
