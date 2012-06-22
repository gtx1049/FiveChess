#ifndef TCPSENDER_H
#define TCPSENDER_H

#include "message.h"
#include "const.h"

class TcpSender
{
public:
    TcpSender(QTcpSocket *tcpSocket);
    bool sendStep(const Message message);
private:
    QTcpSocket *tcpSocket;
};

#endif // TCPSENDER_H
