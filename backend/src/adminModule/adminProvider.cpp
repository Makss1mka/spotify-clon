#include "../headers/adminModule/AdminProvider.h"
#include "../headers/utils/envFile.h"
#include <QFile>
#include <QDebug>
#include <QTextStream>
#include <QString>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>
#include <vector>

AdminProvider::AdminProvider() {}

QByteArray AdminProvider::getAllUserInfo() {
    QFile file(env::get("USERS_INFO_DB", ":/.env"));
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Cannot open env file with path: " << env::get("USERS_INFO_DB", ":/.env");
        return "";
    }

    QJsonArray userArray;
    QJsonObject user;

    // QTextStream in(&file);
    // while (!in.atEnd()) {
    //     QString line = in.readLine();
    //     user["role"] = line.mid(2);
    //     line = in.readLine();
    //     user["id"] = line.mid(2).toInt();
    //     line = in.readLine();
    //     user["name"] = line.mid(2);
    //     line = in.readLine();
    //     user["password"] = line.mid(2);
    //     line = in.readLine();
    //     user["email"] = line.mid(2);
    //     line = in.readLine();
    //     line = in.readLine();
    //     if(line != "au") {
    //         line = in.readLine();
    //         std::vector<int> playlists;


    //     }

    // }

    QByteArray data = "hello";
    return data;
}
