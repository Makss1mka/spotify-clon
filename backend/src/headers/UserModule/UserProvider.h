#ifndef USERPROVIDER_H
#define USERPROVIDER_H

#include "../concepts/Provider.h"
#include "../concepts/Request.h"
#include <QByteArray>
#include <QJsonArray>

class UserProvider : public Provider {
public:
    UserProvider();
    QByteArray registerUser(const QString& login, const QString& email, const QString& password);
    QByteArray authUser(const QString& login, const QString& email, const QString& password);
    void updateBasicInfo(int id, const QString& login, const QString& email, const QString& password);

    void addFavoriteAuthor(int authorId, int userId);
    void deleteFavoriteAuthor(const QString& authorId, const QString& userId);
    QJsonArray getFavoriteAuthors(const QString& userId);

    void addFavoriteMusic(int musicId, int userId);
    void deleteFavoriteMusic(const QString& musicId, const QString& userId);
    QJsonArray getFavoriteMusics(const QString& userId);
};

#endif // USERPROVIDER_H
