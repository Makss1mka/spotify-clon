#ifndef MUSICPROVIDER_H
#define MUSICPROVIDER_H

#include "../concepts/Provider.h"
#include "../concepts/Request.h"
#include <QByteArray>

class MusicProvider : public Provider {
public:
    MusicProvider();
    QByteArray getById(int id);
    QByteArray getFile(std::string path);
    QByteArray getByAuthor(std::string author);
    QByteArray getAll();
};

#endif // MUSICPROVIDER_H
