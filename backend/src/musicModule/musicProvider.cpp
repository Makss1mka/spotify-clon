#include "../headers/musicModule/MusicProvider.h"
#include "../headers/utils/envFile.h"
#include "../headers/concepts/Request.h"
#include "../headers/utils/exceptions.h"
#include "../headers/utils/statusCodes.h"
#include <QDebug>
#include <QByteArray>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>
#include <QSqlQuery>
#include <QString>
#include <QFile>

MusicProvider::MusicProvider() {}

QByteArray MusicProvider::getById(const QString& id) {
    QSqlQuery query;

    if(!query.exec("SELECT * FROM music WHERE id=" + id + ";")) {
        throw ServiceUnavailableException(
            "Method: MusicProvider::getById is unavailable",
            "Music service is temporarily unavailable"
        );
    }

    if(query.next()) {
        QJsonObject musicData;

        musicData["id"] = query.value(0).toInt();
        musicData["name"] = query.value(1).toString();
        musicData["file"] = query.value(2).toString();
        musicData["author_id"] = query.value(3).toString();
        musicData["author_name"] = query.value(4).toString();
        musicData["duration"] = query.value(5).toInt();

        return QJsonDocument(musicData).toJson();
    } else {
        throw NotFoundException(
            "Cannot find music with id: " + id,
            "Music not found"
        );
    }
}

QByteArray MusicProvider::getFile(const QString&  path) {
    QFile file(env::get("MUSIC_DIR", ":/.env") + path);
    if(file.open(QIODevice::ReadOnly)) {
        QByteArray fileContent = file.readAll();
        file.close();
        return fileContent;
    } else {
        throw FileException(
            "Cannot find music file, path: " + path,
            "Cannot find music",
            StatusCode::NOT_FOUND
        );
    }
}

QByteArray MusicProvider::getByAuthor(const QString&  authorName) {
    QSqlQuery query;

    if(!query.exec("SELECT * FROM music WHERE author_name='" + authorName + "' ORDER BY listens DESC;")) {
        throw ServiceUnavailableException(
            "Method: MusicProvider::getByAuthor is unavailable",
            "Music service is temporarily unavailable"
        );
    }

    QJsonArray musicArray;
    QJsonObject musicEntry;

    while(query.next()) {
        musicEntry["id"] = query.value(0).toInt();
        musicEntry["name"] = query.value(1).toString();
        musicEntry["file"] = query.value(2).toString();
        musicEntry["author_id"] = query.value(3).toString();
        musicEntry["author_name"] = query.value(4).toString();
        musicEntry["duration"] = query.value(5).toInt();
        musicEntry["listens"] = query.value(6).toInt();

        musicArray.append(musicEntry);
    }

    return QJsonDocument(musicArray).toJson();
}

QByteArray MusicProvider::getAll() {
    QSqlQuery query;

    if(!query.exec("SELECT * FROM music ORDER BY listens DESC;")) {
        throw ServiceUnavailableException(
            "Method: MusicProvider::getByAuthor is unavailable",
            "Music service is temporarily unavailable"
        );
    }

    QJsonArray musicArray;
    QJsonObject musicEntry;

    while(query.next()) {
        musicEntry["id"] = query.value(0).toInt();
        musicEntry["name"] = query.value(1).toString();
        musicEntry["file"] = query.value(2).toString();
        musicEntry["author_id"] = query.value(3).toString();
        musicEntry["author_name"] = query.value(4).toString();
        musicEntry["duration"] = query.value(5).toInt();
        musicEntry["listens"] = query.value(6).toInt();

        musicArray.append(musicEntry);
    }

    return QJsonDocument(musicArray).toJson();
}

QByteArray MusicProvider::findByName(const QString&  name) {
    QSqlQuery query;

    if(!query.exec("SELECT * FROM music WHERE name LIKE '%" + name + "%' ORDER BY listens DESC;")) {
        throw ServiceUnavailableException(
            "Method: MusicProvider::getByAuthor is unavailable",
            "Music service is temporarily unavailable"
        );
    }

    QJsonArray musicArray;
    QJsonObject musicEntry;

    while(query.next()) {
        musicEntry["id"] = query.value(0).toInt();
        musicEntry["name"] = query.value(1).toString();
        musicEntry["file"] = query.value(2).toString();
        musicEntry["author_id"] = query.value(3).toString();
        musicEntry["author_name"] = query.value(4).toString();
        musicEntry["duration"] = query.value(5).toInt();
        musicEntry["listens"] = query.value(6).toInt();

        musicArray.append(musicEntry);
    }

    return QJsonDocument(musicArray).toJson();
}

QByteArray MusicProvider::find(const QString &keyStr) {
    // QSqlQuery query;

    // if(!query.exec("SELECT * FROM music WHERE name LIKE '%" + name + "%' ORDER BY listens DESC;")) {
    //     throw ServiceUnavailableException(
    //         "Method: MusicProvider::getByAuthor is unavailable",
    //         "Music service is temporarily unavailable"
    //     );
    // }


}
