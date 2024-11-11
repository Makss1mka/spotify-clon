#include "../headers/utils/MusicClass.h"
#include <QJsonObject>
#include <QString>

Music::Music(const QJsonObject &musicObj) {
    id = musicObj.value("id").toInt();
    name = musicObj.value("name").toString();
    author = musicObj.value("author_name").toString();
    authorId = musicObj.value("author_id").toInt();
    duration = musicObj.value("duration").toInt();
    path = musicObj.value("file").toString();
    listens = musicObj.value("listens").toInt();
    janres = musicObj.value("janre").toString();
    lang = musicObj.value("lang").toString();
}

int Music::getId() {
    return id;
}

QString Music::getName() {
    return name;
}

QString Music::getAuthor() {
    return author;
}

int Music::getAuthorId() {
    return authorId;
}

int Music::getDuration() {
    return duration;
}

QString Music::getPath() {
    return path;
}

int Music::getListens() {
    return listens;
}

QString Music::getJanres() {
    return janres;
}

QString Music::getLang() {
    return lang;
}
