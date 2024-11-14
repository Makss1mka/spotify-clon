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
    bool updateBasicInfo(int id, const QString& login, const QString& email, const QString& password, int role);

    void addFavoriteAuthor(int authorId, int userId);
    void deleteFavoriteAuthor(int authorId, int userId);
    QByteArray getFavoriteAuthors(int userId);

    void addFavoriteMusic(int musicId, int userId);
    void deleteFavoriteMusic(int musicId, int userId);
    QByteArray getFavoriteMusics(int userId);
};

#endif // USERPROVIDER_H
