#ifndef MUSICCLASS_H
#define MUSICCLASS_H

#include <QString>
#include <QJsonObject>

class Music {
public:
    Music(const QJsonObject& musicObj);

    int getId();
    QString getName();
    QString getAuthor();
    int getAuthorId();
    int getDuration();
    QString getPath();
    int getListens();
    QString getJanres();
    QString getLang();
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

#endif // MUSICCLASS_H
