#ifndef MUSICPROVIDER_H
#define MUSICPROVIDER_H

#include "../concepts/Provider.h"
#include "../concepts/Request.h"
#include <QByteArray>
#include <QString>

class MusicProvider : public Provider {
public:
    MusicProvider();
    QByteArray getById(const QString& id);
    QByteArray getFile(const QString&  path);
    QByteArray getByAuthor(const QString&  author);
    QByteArray findByName(const QString&  name);
    QByteArray find(const QString& keyStr);
    QByteArray getAll();
    QByteArray recomend(int limit, const QString& janre, const QString& author, const QString& lang, const QString& trackName);
};

#endif // MUSICPROVIDER_H
