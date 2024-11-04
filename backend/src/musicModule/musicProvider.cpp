#include "../headers/musicModule/MusicProvider.h"
#include "../headers/utils/envFile.h"
#include "../headers/concepts/Request.h"
#include <QDebug>
#include <QByteArray>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>
#include <QSqlQuery>
#include <QString>

MusicProvider::MusicProvider() {}

QByteArray MusicProvider::getById(int id) {
    QSqlQuery query;

    if(!query.exec("SELECT * FROM music WHERE id=" + id + ";")) {
        qDebug() << "Cannot select data in method: MusicProvider::getById";
        return "";
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
        return "0";
    }
}

QByteArray MusicProvider::getFile(std::string path) {
    QFile file(env::get("MUSIC_DIR", ":/.env") + path);
    if(file.open(QIODevice::ReadOnly)) {
        QByteArray fileContent = file.readAll();
        file.close();
        return response;
    }
    return "";
}

QByteArray MusicProvider::getByAuthor(std::string author) {

}

QByteArray MusicProvider::getAll() {

}
