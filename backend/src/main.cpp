#include <QCoreApplication>
#include "./headers/concepts/Server.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Server server(3000);

    return a.exec();
}
