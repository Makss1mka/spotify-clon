#include "../headers/userModule/UserProvider.h"
#include "../headers/utils/statusCodes.h"
#include "../headers/utils/exceptions.h"
#include "../headers/concepts/Request.h"
#include "../headers/utils/EnvFile.h"
#include "../headers/concepts/JWT.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QByteArray>
#include <QSqlQuery>
#include <QDateTime>
#include <QString>
#include <QDebug>
#include <QFile>

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
        return authUser(login, email, password);
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
        userData["id"] = query.value(0).toInt();
        userData["login"] = query.value(1).toString();
        userData["role"] = query.value(3).toInt();
        userData["email"] = query.value(4).toString();
        userData["profile"] = query.value(5).toString();

        if(login != "") {
            userData["token"] = QString::fromUtf8(JWT::creaateToken(login, query.value(0).toInt(), Env::get("SECRET"), 3600));
            userData["refreshToken"] = QString::fromUtf8(JWT::creaateToken(login, query.value(0).toInt(), Env::get("SECRET"), 1000000));
        } else {
            userData["token"] = QString::fromUtf8(JWT::creaateToken(email, query.value(0).toInt(), Env::get("SECRET"), 3600));
            userData["refreshToken"] = QString::fromUtf8(JWT::creaateToken(email, query.value(0).toInt(), Env::get("SECRET"), 1000000));
        }
    } else {
        throw QueryException(
            "Invalid account credentials, login|password|email:" + login + ", " + password + ", " + email,
            "Invalid account credentials",
            StatusCode::UNAUTHORIZED
        );
    }

    userData["favAuthors"] = getFavoriteAuthors(query.value(0).toString());
    userData["favMusics"] = getFavoriteMusics(query.value(0).toString());

    QJsonDocument jsonDoc(userData);
    QByteArray jsonData = jsonDoc.toJson();

    return jsonData;
}

QByteArray UserProvider::authUserViaToken(int id) {
    QJsonObject userData;

    QSqlQuery query;
    if(!query.exec("SELECT * FROM userInfo WHERE id=" + QString::number(id) + ";")) {
        throw ServiceUnavailableException(
            "Method: UserProvider::authUserViaToken is unavailable",
            "User service is temporarily unavailable"
        );
    }

    if(query.next()) {
        userData["id"] = query.value(0).toInt();
        userData["login"] = query.value(1).toString();
        userData["role"] = query.value(3).toInt();
        userData["email"] = query.value(4).toString();
        userData["profile"] = query.value(5).toString();
    }

    userData["favAuthors"] = getFavoriteAuthors(query.value(0).toString());
    userData["favMusics"] = getFavoriteMusics(query.value(0).toString());

    QJsonDocument jsonDoc(userData);
    QByteArray jsonData = jsonDoc.toJson();

    return jsonData;
}

QByteArray UserProvider::refreshToken(const QByteArray& refreshToken) {
    QString username = JWT::getUsernameFromToken(refreshToken);
    int id = JWT::getUserIdFromToken(refreshToken);

    QByteArray newToken = JWT::creaateToken(username, id, Env::get("SECRET"), 3600);

    QJsonObject data;
    data["newToken"] = QString::fromUtf8(newToken);

    if(QDateTime::currentSecsSinceEpoch() + 1000 >= JWT::getExpTimeFromToken(refreshToken)) {
        QByteArray newRefreshToken = JWT::creaateToken(username, id, Env::get("SECRET"), 1000000);
        data["newRefrshToken"] = QString::fromUtf8(newRefreshToken);
    }

    return QJsonDocument(data).toJson();;
}

void UserProvider::updateBasicInfo(int id, const QString& login, const QString& email, const QString& password) {
    QSqlQuery query;

    if(login != "" && password != "" && email != "") {
        QString request = "UPDATE userInfo SET ";

        if(login != "") request += " login='" + login + "', ";
        if(email != "") request += " email='" + email + "', ";
        if(password != "") request += " password='" + password + "', ";

        request.replace(request.size() - 2, 1, "");
        request += " WHERE id=" + QString::number(id) + ";";

qDebug() << "REQ " << request;
        if(!query.exec(request)) {
            throw ServiceUnavailableException(
                "Method UserProvider::updateBasicInfo: incorrect db request",
                "incorrect db request"
            );
        }
    }
}

QByteArray UserProvider::updateProfile(const QString& id, const QByteArray& profile) {
    if(profile == "") {
        throw BadRequestException(
            "Invalid body format for update user profile, empty body",
            "Invalid body format for update user profile, empty body"
        );
    }

    QSqlQuery query;

    if(!query.exec("SELECT userInfo.picture FROM userInfo WHERE id=" + id + ";")) {
        throw ServiceUnavailableException(
            "Method UserProvider::updateBasicInfo: incorrect db request",
            "incorrect db request"
        );
    }

    QString path = "";
    if(!query.next()) {
        throw ServiceUnavailableException(
            "Method UserProvider::updateBasicInfo: cannot find user with such id",
            "Cannot find user with such id"
        );
    } else if(query.value(0).isNull() == true) {
        if(!query.exec("SELECT COUNT(*) FROM userINfo WHERE SUBSTR(picture, 1, 1) = 'u'")) {
            throw ServiceUnavailableException(
                "Method UserProvider::updateBasicInfo: incorrect db request",
                "incorrect db request"
            );
        }

        if(query.next()) {
            path = "u_" + QString::number(query.value(0).toInt() + 1) + ".jpg";
            qDebug() << "PATH: " << path;
        }
    } else {
        path = query.value(0).toString();
    }

    qDebug() << "PATH 111: " << path << " len - " << profile.size();
    if(path != "") {
        QFile file(Env::get("PROFILES_DIR") + path);
        if (!file.open(QIODevice::WriteOnly)) {
            throw FileException(
                "Cannot open file for writing profile, path: " + path,
                "Cannot open file for writing profile",
                StatusCode::NOT_FOUND
            );
        } else {
            qint64 bytesWritten = file.write(profile);
            if (bytesWritten == -1) {
                throw FileException(
                    "Cannot write profile file, path: " + path,
                    "Cannot write profile file",
                    StatusCode::NOT_FOUND
                );
            }
            file.close();

            if(!query.exec("UPDATE userInfo SET picture='" + path + "' WHERE id=" + id + ";")) {
                throw ServiceUnavailableException(
                    "Method UserProvider::updateBasicInfo: incorrect db request, cannot set profile picture path",
                    "incorrect db request"
                );
            }

            return path.toUtf8();
        }
    }
}

void UserProvider::addFavoriteAuthor(int authorId, int userId) {
    QSqlQuery query;
    if(!query.exec("SELECT login FROM userInfo WHERE id=" + QString::number(authorId) + ";")) {
        throw ServiceUnavailableException(
            "Method: UserProvider::addFavoriteAuthor is unavailable",
            "User service is temporarily unavailable"
        );
    }

    if(!query.next()) {
        throw ConflictDbException(
            "Author with such id doesn't exist",
            "Author with such id doesn't exist"
        );
    }

    if(!query.exec("INSERT INTO user_author (author_id, user_id) VALUES (" + QString::number(authorId) + ", " + QString::number(userId) + ");")) {
        throw ServiceUnavailableException(
            "Method: UserProvider::addFavoriteAuthor is unavailable",
            "User service is temporarily unavailable"
        );
    }
}

void UserProvider::deleteFavoriteAuthor(const QString& authorId, const QString& userId) {
    QSqlQuery query;
    if(!query.exec("DELETE FROM user_author WHERE user_id=" + userId + " and author_id=" + authorId + ";")) {
        throw ServiceUnavailableException(
            "Method: UserProvider::deleteFavoriteAuthor is unavailable",
            "User service is temporarily unavailable"
        );
    }
}

QJsonArray UserProvider::getFavoriteAuthors(const QString& userId) {
    QJsonArray resultArray;
    QJsonObject authoeEntry;
    QSqlQuery query;

    if(!query.exec("SELECT userInfo.id, userInfo.login, userInfo.picture FROM user_author JOIN userInfo ON userInfo.id=user_author.author_id WHERE user_author.user_id=" + userId + ";")) {
        throw ServiceUnavailableException(
            "Method: UserProvider::getFavoriteAuthor is unavailable",
            "User service is temporarily unavailable"
        );
    }

    while(query.next()) {
        authoeEntry["id"] = query.value(0).toInt();
        authoeEntry["name"] = query.value(1).toString();
        authoeEntry["profile"] = query.value(2).toString();

        resultArray.append(authoeEntry);
    }

    return resultArray;
}


void UserProvider::addFavoriteMusic(int musicId, int userId) {
    QSqlQuery query;
    if(!query.exec("SELECT name FROM music WHERE id=" + QString::number(musicId) + ";")) {
        throw ServiceUnavailableException(
            "Method: UserProvider::addFavoriteMusic is unavailable",
            "User service is temporarily unavailable"
        );
    }

    if(!query.next()) {
        throw ConflictDbException(
            "Music with such id doesn't exist",
            "Music with such id doesn't exist"
        );
    }

    if(!query.exec("INSERT INTO user_music (user_id, music_id) VALUES (" +  QString::number(userId) + ", " + QString::number(musicId) + ");")) {
        throw BadRequestException(
            "Query execution failed",
            "Query execution failed"
        );
    }
}

void UserProvider::deleteFavoriteMusic(const QString& musicId, const QString& userId) {
    QSqlQuery query;
    if(!query.exec("DELETE FROM user_music WHERE user_id=" + userId + " and music_id=" + musicId + ";")) {
        throw ServiceUnavailableException(
            "Method: UserProvider::deleteFavoriteAuthor is unavailable",
            "User service is temporarily unavailable"
        );
    }
}

QJsonArray UserProvider::getFavoriteMusics(const QString& userId) {
    QJsonArray resultArray;
    QJsonObject musicEntry;
    QSqlQuery query;

    if(!query.exec("SELECT music.id, music.name, music.file, music.author_id, userInfo.login, music.duration, music.listens, "
        "music.janre, music.lang, music.picture AS musicPic, userInfo.picture AS userPic FROM user_music "
        "JOIN music ON user_music.music_id = music.id "
        "JOIN userInfo ON music.author_id = userInfo.id "
        "WHERE user_music.user_id=" + userId + ";")) {
        throw ServiceUnavailableException(
            "Method: UserProvider::getFavoriteMusics is unavailable",
            "User service is temporarily unavailable"
        );
    }

    while(query.next()) {
        musicEntry["id"] = query.value(0).toInt();
        musicEntry["name"] = query.value(1).toString();
        musicEntry["file"] = query.value(2).toString();
        musicEntry["author_id"] = query.value(3).toInt();
        musicEntry["author_name"] = query.value(4).toString();
        musicEntry["duration"] = query.value(5).toInt();
        musicEntry["listens"] = query.value(6).toInt();
        musicEntry["janre"] = query.value(7).toString();
        musicEntry["lang"] = query.value(8).toString();
        musicEntry["profile"] = query.value(9).toString();
        musicEntry["author_profile"] = query.value(10).toString();

        resultArray.append(musicEntry);
    }

    return resultArray;
}


