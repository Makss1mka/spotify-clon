#include <QCoreApplication>
#include "./headers/concepts/Server.h"
#include "./headers/utils/envFile.h"
#include <QString>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Server server(Env::get("PORT", ":/.env").toInt());

    return a.exec();
}
