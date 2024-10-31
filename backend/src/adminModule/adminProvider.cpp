#include "../headers/adminModule/AdminProvider.h"
#include "../headers/utils/envFile.h"
#include <QDebug>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>
#include <QSqlQuery>

AdminProvider::AdminProvider() {}

QByteArray AdminProvider::getAllUserInfo() {
    QJsonArray userArray;
    QJsonObject user;

    QSqlQuery query;
    if(!query.exec("SELECT * FROM userInfo")) {
        qDebug() << "Cannot select data in method: getAllUserInfo";
        return "";
    }

    while (query.next()) {
        user["id"] = query.value(0).toInt();
        user["login"] = query.value(1).toString();
        user["role"] = query.value(3).toInt();
        user["email"] = query.value(4).toString();
        userArray.append(user);
    }

    QJsonDocument jsonDoc(userArray);
    QByteArray jsonData = jsonDoc.toJson();

    return jsonData;
}
