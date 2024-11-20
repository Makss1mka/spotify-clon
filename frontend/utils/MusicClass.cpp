#include "../headers/utils/MusicClass.h"
#include <QJsonObject>
#include <QString>

MusicObject::MusicObject(const QJsonObject &musicObj) {
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

int MusicObject::getId() {
    return id;
}

QString MusicObject::getName() {
    return name;
}

QString MusicObject::getAuthor() {
    return author;
}

int MusicObject::getAuthorId() {
    return authorId;
}

int MusicObject::getDuration() {
    return duration;
}

QString MusicObject::getPath() {
    return path;
}

int MusicObject::getListens() {
    return listens;
}

QString MusicObject::getJanres() {
    return janres;
}

QString MusicObject::getLang() {
    return lang;
}

QString MusicObject::getAllData() {
    return QString::number(id) + " " + name + " " + author + " " + QString::number(authorId) + " " + path
        + " " + QString::number(listens) + " " + janres + " " + lang;
}





AuthorObject::AuthorObject(const QJsonObject &authorObj) {
    id = authorObj.value("id").toInt();
    name = authorObj.value("name").toString();
}

int AuthorObject::getId() {
    return id;
}

QString AuthorObject::getName() {
    return name;
}
