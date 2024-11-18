#ifndef USERPROVIDER_H
#define USERPROVIDER_H

#include "../concepts/Provider.h"
#include "../concepts/Request.h"
#include <QByteArray>

class UserProvider : public Provider {
public:
    UserProvider();
    QByteArray registerUser(const QString& login, const QString& email, const QString& password);
    QByteArray authUser(const QString& login, const QString& email, const QString& password);
    void updateBasicInfo(const QString& id, const QString& login, const QString& email, const QString& password, const QString& role);

    void addFavoriteAuthor(const QString& authorId, const QString& userId);
    void deleteFavoriteAuthor(const QString& authorId, const QString& userId);
    QByteArray getFavoriteAuthors(const QString& userId);

    void addFavoriteMusic(const QString& musicId, const QString& userId);
    void deleteFavoriteMusic(const QString& musicId, const QString& userId);
    QByteArray getFavoriteMusics(const QString& userId);
};

#endif // USERPROVIDER_H
