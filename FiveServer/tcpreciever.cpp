#include "tcpreciever.h"
#include <iostream>
using namespace std;
TcpReciever::TcpReciever(QTcpSocket *tcpSocket)
{
    this->tcpSocket = tcpSocket;
}

bool TcpReciever::recieveStep(Message &message)
{
    quint16 status = 0;
    quint16 blockSize = 0;
    QDataStream in(tcpSocket);
    in.setVersion(QDataStream::Qt_4_6);

    if(tcpSocket->bytesAvailable() < (int)sizeof(quint16))
    {
        return false;
    }
    in >> blockSize;

    if(tcpSocket->bytesAvailable() < blockSize)
    {
        return false;
    }

    in >> status;
    message.status = status;
    switch(status)
    {
    case CONNECT:
        in >> message.clientName;
        break;
    case JOIN:
        in >> message.rivalName;
        break;
    }

    return true;
}
