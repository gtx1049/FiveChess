#ifndef MESSAGE_H
#define MESSAGE_H
#include <QtNetwork>

typedef struct tag_point
{
    quint16  x;
    quint16  y;
} Point;

class Message
{
public:
    int status;
    QString clientName;
    QString rivalName;
    QString ipAddress;
    QVector<QString> playerNames;
    Point point;
};

#endif // MESSAGE_H
