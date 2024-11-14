#include "../headers/userModule/UserProvider.h"
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

UserProvider::UserProvider() {}

QByteArray UserProvider::registerUser(const QString& login, const QString& email, const QString& password) {
    QSqlQuery query;
    if(!query.exec("SELECT * FROM userInfo WHERE login='" + login + "' or email='" + email + "';")) {
        throw ServiceUnavailableException("Method: UserProvider::registerUser is unavailable", "User service is temporarily unavailable");
    }

    if(query.next()) {
        if(query.value(1).toString() == login) {
            throw ConflictDbException(
                "User with this login is actualy exist, " + login + ", " + password + ", " + email,
                "User with this login is actualy exist"
            );
        } else {
            throw ConflictDbException(
                "User with this email is actualy exist, " + login + ", " + password + ", " + email,
                "User with this email is actualy exist"
            );
        }
    } else {
        if(!query.exec("INSERT INTO userInfo (login, password, role, email) VALUES ('" + login + "', '" + password + "', 0, '" + email + "');")) {
            throw ServiceUnavailableException(
                "Cannot select data in method: UserProvider::registerUser",
                "User service is temporarily unavailable"
            );
        }
        return "User was successfuly created";
    }
}

QByteArray UserProvider::authUser(const QString& login, const QString& email, const QString& password) {
    QJsonObject userData;

    QSqlQuery query;
    if(!query.exec("SELECT * FROM userInfo WHERE (login='" + login + "' or email='" + email + "') and password='" + password + "';")) {
        throw ServiceUnavailableException(
            "Method: UserProvider::authUser is unavailable",
            "User service is temporarily unavailable"
        );
    }

    if(query.next()) {
        userData["login"] = query.value(1).toString();
        userData["role"] = query.value(3).toInt();
        userData["email"] = query.value(4).toString();
    } else {
        throw QueryException(
            "Invalid account credentials, login|password|email:" + login + ", " + password + ", " + email,
            "Invalid account credentials",
            StatusCode::UNAUTHORIZED
        );
    }

    QJsonDocument jsonDoc(userData);
    QByteArray jsonData = jsonDoc.toJson();

    return jsonData;
}

void UserProvider::updateBasicInfo(int id, const QString& login, const QString& email, const QString& password, int role) {
    QSqlQuery query;
    if(!query.exec("UPDATE userInfo SET login='" + login + "', email='" + email + "', "
            "password='" + password + "', role=" + QString::number(role) + " WHERE id=" + QString::number(id) + ";")) {
        throw ServiceUnavailableException(
            "Method: UserProvider::updateBasicInfo is unavailable",
            "User service is temporarily unavailable"
        );
    }
}

void addFavoriteAuthor(int authorId, int userId) {
    QSqlQuery query;
    if(!query.exec("INSERT INTO user_author (author_id, user_id) VALUES (" + QString::number(authorId) + ", " + QString::number(userId) + ");")) {
        throw ServiceUnavailableException(
            "Method: UserProvider::addFavoriteAuthor is unavailable",
            "User service is temporarily unavailable"
        );
    }
}

void deleteFavoriteAuthor(int authorId, int userId) {
    QSqlQuery query;
    if(!query.exec("DELETE FROM user_author WHERE user_id=" + QString::number(userId) + " and author_id=" + QString::number(authorId) + ";")) {
        throw ServiceUnavailableException(
            "Method: UserProvider::deleteFavoriteAuthor is unavailable",
            "User service is temporarily unavailable"
        );
    }
}

QByteArray getFavoriteAuthors(int userId) {
    QJsonArray resultArray;
    QJsonObject authoeEntry;
    QSqlQuery query;

    if(!query.exec("SELECT authors.id, authors.name FROM user_author JOIN authors ON authors.id=user_author.author_id WHERE user_author.user_id=" + QString::number(userId) + ";")) {
        throw ServiceUnavailableException(
            "Method: UserProvider::getFavoriteMusics is unavailable",
            "User service is temporarily unavailable"
        );
    }

    while(query.next()) {
        authoeEntry["id"] = query.value(0).toInt();
        authoeEntry["name"] = query.value(1).toString();

        musicArray.append(authoeEntry);
    }

    return QJsonDocument(resultArray).toJson();
}

void addFavoriteMusic(int musicId, int userId) {
    QSqlQuery query;
    if(!query.exec("INSERT INTO user_music (user_id, music_id) VALUES (" + QString::number(userId) + ", " + QString::number(musicId) + ");")) {
        throw ServiceUnavailableException(
            "Method: UserProvider::addFavoriteMusic is unavailable",
            "User service is temporarily unavailable"
        );
    }
}

void deleteFavoriteMusic(int musicId, int userId) {
    QSqlQuery query;
    if(!query.exec("DELETE FROM user_music WHERE user_id=" + QString::number(userId) + " and music_id=" + QString::number(musicId) + ";")) {
        throw ServiceUnavailableException(
            "Method: UserProvider::deleteFavoriteAuthor is unavailable",
            "User service is temporarily unavailable"
        );
    }
}

QByteArray getFavoriteMusics(int userId) {
    QJsonArray resultArray;
    QJsonObject musicEntry;
    QSqlQuery query;

    if(!query.exec("SELECT music.id, music.name, music.file, music.author_id, music.author_name, music.duration, music.listens, music.janre, music.lang"
        " FROM user_music JOIN music ON music.id=user_music.music_id WHERE user_music.user_id=" + QString::number(userId) + ";")) {
        throw ServiceUnavailableException(
            "Method: UserProvider::getFavoriteMusics is unavailable",
            "User service is temporarily unavailable"
        );
    }

    while(query.next()) {
        musicEntry["id"] = query.value(0).toInt();
        musicEntry["name"] = query.value(1).toString();
        musicEntry["file"] = query.value(2).toString();
        musicEntry["author_id"] = query.value(3).toString();
        musicEntry["author_name"] = query.value(4).toString();
        musicEntry["duration"] = query.value(5).toInt();
        musicEntry["listens"] = query.value(6).toInt();
        musicEntry["janre"] = query.value(7).toString();
        musicEntry["lang"] = query.value(8).toString();

        musicArray.append(musicEntry);
    }

    return QJsonDocument(resultArray).toJson();
}









