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
    int getDuration();
    QString getPath();
    int getListens();
    QString getJanres();
    QString getLang();
    QString getAllData();
private:
    int id;
    QString name;
    QString author;
    int authorId;
    int duration;
    QString path;
    int listens;
    QString janres;
    QString lang;
};

class AuthorObject {
public:
    AuthorObject(const QJsonObject& authorObj);

    int getId();
    QString getName();
private:
    int id;
    QString name;
};

#endif // MUSICCLASS_H
