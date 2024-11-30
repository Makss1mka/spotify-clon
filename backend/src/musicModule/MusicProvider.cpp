#include "../headers/musicModule/MusicProvider.h"
#include "../headers/utils/EnvFile.h"
#include "../headers/concepts/Request.h"
#include "../headers/utils/exceptions.h"
#include "../headers/utils/statusCodes.h"
#include <QByteArray>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>
#include <QSqlQuery>
#include <QString>
#include <QFile>
#include <QList>
#include <vector>

MusicProvider::MusicProvider() {}

QByteArray MusicProvider::getById(const QString& id) {
    QSqlQuery query;

    if(!query.exec("SELECT music.id, music.name, music.file, userInfo.id, userInfo.login, music.duration, music.listens, "
        "music.janre, music.lang, music.picture AS musicPic, userInfo.picture AS userPic FROM music JOIN userInfo on music.author_id=userInfo.id WHERE music.id=" + id + ";")) {
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
        musicData["author_id"] = query.value(3).toInt();
        musicData["author_name"] = query.value(4).toString();
        musicData["duration"] = query.value(5).toInt();
        musicData["listens"] = query.value(6).toInt();
        musicData["janre"] = query.value(7).toString();
        musicData["lang"] = query.value(8).toString();
        musicData["profile"] = query.value(9).toString();
        musicData["author_profile"] = query.value(10).toString();

        return QJsonDocument(musicData).toJson();
    } else {
        throw NotFoundException(
            "Cannot find music with id: " + id,
            "Music not found"
        );
    }
}

QByteArray MusicProvider::getFile(const QString&  path) {
    QFile file(path);
    if(file.open(QIODevice::ReadOnly)) {
        QByteArray fileContent = file.readAll();
        file.close();
        return fileContent;
    } else {
        throw FileException(
            "Cannot find file, path: " + path,
            "Cannot find file",
            StatusCode::NOT_FOUND
        );
    }
}

QByteArray MusicProvider::getByAuthor(const QString&  authorName) {
    QSqlQuery query;

    if(!query.exec("SELECT music.id, music.name, music.file, userInfo.id, userInfo.login, music.duration, music.listens, "
        "music.janre, music.lang, music.picture AS musicPic, userInfo.picture AS userPic FROM music JOIN userInfo on music.author_id=userInfo.id WHERE userInfo.login='" + authorName + "' ORDER BY listens DESC;")) {
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
        musicEntry["author_id"] = query.value(3).toInt();
        musicEntry["author_name"] = query.value(4).toString();
        musicEntry["duration"] = query.value(5).toInt();
        musicEntry["listens"] = query.value(6).toInt();
        musicEntry["janre"] = query.value(7).toString();
        musicEntry["lang"] = query.value(8).toString();
        musicEntry["profile"] = query.value(9).toString();
        musicEntry["author_profile"] = query.value(10).toString();

        musicArray.append(musicEntry);
    }

    return QJsonDocument(musicArray).toJson();
}

QByteArray MusicProvider::getAll() {
    QSqlQuery query;

    if(!query.exec("SELECT music.id, music.name, music.file, userInfo.id, userInfo.login, music.duration, music.listens, "
        "music.janre, music.lang, music.picture AS musicPic, userInfo.picture AS userPic FROM music JOIN userInfo on music.author_id=userInfo.id ORDER BY music.listens DESC;")) {
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
        musicEntry["author_id"] = query.value(3).toInt();
        musicEntry["author_name"] = query.value(4).toString();
        musicEntry["duration"] = query.value(5).toInt();
        musicEntry["listens"] = query.value(6).toInt();
        musicEntry["janre"] = query.value(7).toString();
        musicEntry["lang"] = query.value(8).toString();
        musicEntry["profile"] = query.value(9).toString();
        musicEntry["author_profile"] = query.value(10).toString();

        musicArray.append(musicEntry);
    }

    return QJsonDocument(musicArray).toJson();
}

QByteArray MusicProvider::findByName(const QString&  name) {
    QSqlQuery query;

    if(!query.exec("SELECT music.id, music.name, music.file, userInfo.id, userInfo.login, music.duration, music.listens, music.janre, music.lang, "
        "music.picture AS musicPic, userInfo.picture AS userPic FROM music JOIN userInfo on music.author_id=userInfo.id WHERE music.name LIKE '%" + name + "%' ORDER BY music.listens DESC;")) {
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
        musicEntry["author_id"] = query.value(3).toInt();
        musicEntry["author_name"] = query.value(4).toString();
        musicEntry["duration"] = query.value(5).toInt();
        musicEntry["listens"] = query.value(6).toInt();
        musicEntry["janre"] = query.value(7).toString();
        musicEntry["lang"] = query.value(8).toString();
        musicEntry["profile"] = query.value(9).toString();
        musicEntry["author_profile"] = query.value(10).toString();

        musicArray.append(musicEntry);
    }

    return QJsonDocument(musicArray).toJson();
}

QByteArray MusicProvider::find(const QString &keyStr) {
    QJsonObject result;
    QSqlQuery query;
    QList<QString> keyWords = keyStr.split(" ");

    QJsonArray musicArray;
    QJsonObject musicEntry;

    QJsonArray authorArray;
    QJsonObject authorEntry;

    QString requestTemplate = "SELECT music.id, music.name, music.file, userInfo.id, userInfo.login, music.duration, music.listens, "
        "music.janre, music.lang, music.picture AS musicPic, userInfo.picture AS userPic FROM music "
        "JOIN userInfo on music.author_id=userInfo.id WHERE ";
    QString sorting = " ORDER BY music.listens DESC LIMIT 10;";
    QString likeTracksTemplates = "";
    QString likeAuthorsTemplates = "";

    for(int i = 0; i < keyWords.size(); i++) {
        likeTracksTemplates += " ' ' || music.name || ' ' || userInfo.login || ' ' LIKE '% " + keyWords[i] + "% %' ";
        likeAuthorsTemplates += " ' ' || userInfo.login || ' ' LIKE '% " + keyWords[i] + "% %' ";

        if (i != keyWords.size() - 1) {
            likeTracksTemplates += " AND ";
            likeAuthorsTemplates += " AND ";
        }
    }

    //qDebug() << " find 111 " << requestTemplate + likeTracksTemplates + sorting;
    if(!query.exec(requestTemplate + likeTracksTemplates + sorting)) {
        throw ServiceUnavailableException(
            "Method: MusicProvider::find is unavailable",
            "Music service is temporarily unavailable"
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

        musicArray.append(musicEntry);
    }

    QString requestStringForAuthors = "SELECT id, login, picture FROM userInfo WHERE ";
    qDebug() << " find 222 " << requestStringForAuthors + likeAuthorsTemplates + " ORDER BY RANDOM() LIMIT 10";
    if(!query.exec(requestStringForAuthors + likeAuthorsTemplates + " ORDER BY RANDOM() LIMIT 10")) {
        throw ServiceUnavailableException(
            "Method: MusicProvider::find is unavailable",
            "Music service is temporarily unavailable"
        );
    }

    while(query.next()) {
        authorEntry["id"] = query.value(0).toInt();
        authorEntry["name"] = query.value(1).toString();
        authorEntry["profile"] = query.value(2).toString();

        authorArray.append(authorEntry);
    }

    result["musics"] = musicArray;
    result["authors"] = authorArray;
    return QJsonDocument(result).toJson();
}

QByteArray MusicProvider::recomend(int limit, const QString& janre, const QString& author, const QString& lang, const QString& trackName) {
    QList<QString> janres = janre.split(",");
    std::vector<int> ids;
    QSqlQuery query;

    QJsonArray musicArray;
    QJsonObject musicEntry;

    QString requestTemplate = "SELECT music.id, music.name, music.file, userInfo.id, userInfo.login AS author, music.duration, music.listens, "
            "music.janre AS janre, music.lang AS lang, music.picture AS musicPic, userInfo.picture AS userPic FROM music "
            "JOIN userInfo ON music.author_id=userInfo.id WHERE music.name != '" + trackName + "' AND ";
    QString requestSorting = " ORDER BY RANDOM();";

    std::function<void(void)> addEntries = [&limit, &query, &musicArray, &musicEntry, &ids](){
        while(query.next() && musicArray.size() < limit) {
            bool isExist = false;
            for(int i = 0; i < ids.size(); i++) {
                if (ids[i] == query.value(0).toInt()) {
                    isExist = true;
                    break;
                }
            }
            if(isExist == true) continue;

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

            ids.push_back(query.value(0).toInt());
            musicArray.append(musicEntry);
        }
    };

    QString where = "";
    for(int i = 0; i < janres.size(); i++) {
        where += " janre LIKE '%" + janres[i] + ",%' AND ";
    }

    // FIRST STAGE
    //qDebug() << " 111 " << requestTemplate + where + " lang = '" + lang + "' AND author != '" + author +  "' " + requestSorting;
    if(!query.exec(requestTemplate + where + " lang = '" + lang + "' AND author != '" + author +  "' " + requestSorting)) {
        throw ServiceUnavailableException(
            "Method: MusicProvider::recomend is unavailable",
            "Music service is temporarily unavailable"
        );
    }

    addEntries();
    if (musicArray.size() >= limit) return QJsonDocument(musicArray).toJson();


    // SECOND STAGE
    ///qDebug() << " 222 " << requestTemplate + where + " lang = '" + lang +  "' " + requestSorting;
    if(!query.exec(requestTemplate + where + " lang = '" + lang +  "' " + requestSorting)) {
        throw ServiceUnavailableException(
            "Method: MusicProvider::recomend is unavailable",
            "Music service is temporarily unavailable"
            );
    }

    addEntries();
    if (musicArray.size() >= limit) return QJsonDocument(musicArray).toJson();


    // THIRD STAGE
    //qDebug() << " 333 " << requestTemplate + where + " lang != '" + lang +  "' " + requestSorting;
    if(!query.exec(requestTemplate + where + " lang != '" + lang +  "' " + requestSorting)) {
        throw ServiceUnavailableException(
            "Method: MusicProvider::recomend is unavailable",
            "Music service is temporarily unavailable"
        );
    }

    addEntries();
    if (musicArray.size() >= limit) return QJsonDocument(musicArray).toJson();


    // FOURTH STAGE
    for(int i = 0; i < janres.size(); i++) {
        //qDebug() << " 444 " << requestTemplate + " janre LIKE '%" + janres[i] + ",%' AND " + " lang = '" + lang +  "' AND author != '" + author +  "' " + requestSorting;
        if(!query.exec(requestTemplate + " janre LIKE '%" + janres[i] + ",%' AND " + " lang = '" + lang +  "' AND author != '" + author +  "' " + requestSorting)) {
            throw ServiceUnavailableException(
                "Method: MusicProvider::recomend is unavailable",
                "Music service is temporarily unavailable"
            );
        }

        addEntries();
        if (musicArray.size() >= limit) return QJsonDocument(musicArray).toJson();
    }


    // FIFTH STAGE
    for(int i = 0; i < janres.size(); i++) {
        //qDebug() << " 555 " << requestTemplate + " janre LIKE '%" + janres[i] + ",%' AND " + " lang = '" + lang +  "' " + requestSorting;
        if(!query.exec(requestTemplate + " janre LIKE '%" + janres[i] + ",%' AND " + " lang = '" + lang +  "' " + requestSorting)) {
            throw ServiceUnavailableException(
                "Method: MusicProvider::recomend is unavailable",
                "Music service is temporarily unavailable"
            );
        }

        addEntries();
        if (musicArray.size() >= limit) return QJsonDocument(musicArray).toJson();
    }

    // SIXTH STAGE
    for(int i = 0; i < janres.size(); i++) {
        //qDebug() << " 666 " << requestTemplate + " janre LIKE '%" + janres[i] + ",%' " + requestSorting;
        if(!query.exec(requestTemplate + " janre LIKE '%" + janres[i] + ",%' " + requestSorting)) {
            throw ServiceUnavailableException(
                "Method: MusicProvider::recomend is unavailable",
                "Music service is temporarily unavailable"
            );
        }

        addEntries();
        if (musicArray.size() >= limit) return QJsonDocument(musicArray).toJson();
    }

    // SEVENTH STAGE
    //qDebug() << " 777 " << requestTemplate + " author = '" + author +  "' " + requestSorting;
    if(!query.exec(requestTemplate + " author = '" + author +  "' " + requestSorting)) {
        throw ServiceUnavailableException(
            "Method: MusicProvider::recomend is unavailable",
            "Music service is temporarily unavailable"
        );
    }

    addEntries();
    if (musicArray.size() >= limit) return QJsonDocument(musicArray).toJson();


    // EIGHTTH STAGE
    //qDebug() << " 888 " << requestTemplate + " lang = '" + lang +  "' " + requestSorting;
    if(!query.exec(requestTemplate + " lang = '" + lang +  "' " + requestSorting)) {
        throw ServiceUnavailableException(
            "Method: MusicProvider::recomend is unavailable",
            "Music service is temporarily unavailable"
        );
    }

    addEntries();

    return QJsonDocument(musicArray).toJson();
}
