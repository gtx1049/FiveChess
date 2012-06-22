#ifndef MESSAGE_H
#define MESSAGE_H
#include "QtNetwork"

class Message
{
public:
    int status;
    QString clientName;
    QString rivalName;
    QString ipAddress;
    QVector<QString> playerNames;
};

#endif // MESSAGE_H
