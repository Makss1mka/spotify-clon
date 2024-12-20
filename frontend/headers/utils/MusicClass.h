#ifndef MUSICCLASS_H
#define MUSICCLASS_H

#include <QString>
#include <QJsonObject>

class MusicObject {
public:
    MusicObject(const QJsonObject& musicObj);

    int getId();
    QString getName();
    QString getAuthor();
    int getAuthorId();
    QString getAuthorProfilePath();
    QString getPath();
    int getListens();
    QString getJanres();
    QString getLang();
    QString getProfilePath();
    QString getAllData();
private:
    int id;
    QString name;
    QString author;
    int authorId;
    QString authorProfilePath;
    QString path;
    int listens;
    QString janres;
    QString lang;
    QString profilePath;
};

class AuthorObject {
public:
    AuthorObject(const QJsonObject& authorObj);

    int getId();
    QString getName();
    QString getProfilePath();
private:
    int id;
    QString name;
    QString profilePath;
};

#endif // MUSICCLASS_H
