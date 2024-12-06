#include "./headers/concepts/Server.h"
#include "./headers/utils/envFile.h"
#include <QCoreApplication>
#include <stdexcept>
#include <QString>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Server server(Env::get("PORT").toInt());

    return a.exec();
}
