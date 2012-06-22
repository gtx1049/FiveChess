#include "tcpsender.h"
#include <iostream>
using namespace std;
TcpSender::TcpSender(QTcpSocket *tcpSocket)
{
    this->tcpSocket = tcpSocket;
}

bool TcpSender::sendStep(const Message message)
{
    QByteArray block;
    QDataStream out(&block,QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_6);

    out << (quint16) 0;
    out << (quint16) message.status;

    switch(message.status)
    {
    case CONNECT:
        out << message.clientName;
        break;
    case JOIN:
        out << message.rivalName;
        break;
    case DOWN:
        out << message.point.x;
        out << message.point.y;
        break;
    case UNDO:
        break;
    case LIST:
        out << message.playerNames;
        break;
    }

    out.device()->seek(0);
    out << (quint16) (block.size() - sizeof(quint16));
    tcpSocket->write(block);

    return true;
}
