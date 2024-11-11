#ifndef MUSICPROVIDER_H
#define MUSICPROVIDER_H

#include "../concepts/Provider.h"
#include "../concepts/Request.h"
#include <QByteArray>

class MusicProvider : public Provider {
public:
    MusicProvider();
    QByteArray getById(const QString& id);
    QByteArray getFile(const QString&  path);
    QByteArray getByAuthor(const QString&  author);
    QByteArray findByName(const QString&  name);
    QByteArray find(const QString& keyStr);
    QByteArray getAll();
    QByteArray recomend(std::vector<QString>& janres, std::vector<QString> authors, std::vector<QString> langs);
};

#endif // MUSICPROVIDER_H
