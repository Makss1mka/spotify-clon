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
    QByteArray addMusicBasicInfo(int authorId, const QString& name, const QString& lang, const QString& janres);
    void addMusicFile(int musicId, const QByteArray& music);
    void addMusicProfile(int musicId, const QString& profileType, const QByteArray& profile);
    void updateMusic(int musicId, const QString& name, const QString& lang, const QString& janres);
};

#endif // MUSICPROVIDER_H
