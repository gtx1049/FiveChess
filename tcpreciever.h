#ifndef TCPRECIEVER_H
#define TCPRECIEVER_H

#include "tcpsender.h"

class TcpReciever
{
public:
    TcpReciever(QTcpSocket *tcpSocket);
    bool recieveStep(Message &message);
private:
    QTcpSocket *tcpSocket;
};

#endif // TCPRECIEVER_H
