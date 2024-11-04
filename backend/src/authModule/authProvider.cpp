#include "../headers/authModule/AuthProvider.h"
#include "../headers/utils/envFile.h"
#include "../headers/concepts/Request.h"
#include "../headers/utils/exceptions.h"
#include "../headers/utils/statusCodes.h"
#include <QDebug>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>
#include <QSqlQuery>
#include <QString>

AuthProvider::AuthProvider() {}

QByteArray AuthProvider::registerUser(QString& login, QString& email, QString& password) {
    QSqlQuery query;
    if(!query.exec("SELECT * FROM userInfo WHERE login='" + login + "' or email='" + email + "';")) {
        throw DbException(
            "Cannot select data in method: AuthProvider::registerUser",

            );
    }

    if(query.next()) {
        if(query.value(1).toString() == login) {
            return "1";
        } else {
            return "2";
        }
    } else {
        if(!query.exec("INSERT INTO userInfo (login, password, role, email) VALUES ('" + login + "', '" + password + "', 0, '" + email + "');")) {
            qDebug() << "Cannot insert data in method: AuthProvider::registerUser";
            return "";
        }
        return "0";
    }
}

QByteArray AuthProvider::authUser(QString& login, QString& email, QString& password) {
    QJsonObject userData;

    QSqlQuery query;
    if(!query.exec("SELECT * FROM userInfo WHERE (login='" + login + "' or email='" + email + "') and password='" + password + "';")) {
        qDebug() << "Cannot select data in method: AuthProvider::registerUser";
        return "503";
    }

    if(query.next()) {
        userData["login"] = query.value(1).toString();
        userData["role"] = query.value(3).toInt();
        userData["email"] = query.value(4).toString();
    } else {
        return "401";
    }

    QJsonDocument jsonDoc(userData);
    QByteArray jsonData = jsonDoc.toJson();

    return jsonData;
}
