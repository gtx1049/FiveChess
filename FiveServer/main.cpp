#include <QtCore/QCoreApplication>
#include "server.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    //Server *server = new Server();
    new Server();
    return a.exec();
}
