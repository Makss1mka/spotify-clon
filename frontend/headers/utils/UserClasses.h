#ifndef USERCLASSES_H
#define USERCLASSES_H

#include "./MusicClass.h"
#include <QJsonObject>
#include <QString>
#include <vector>

class Author;

class User {
protected:
    User();

    static int id;
    static QString name;
    static QString password;
    static QString email;
    static int role;

    static QString token;
    static QString refreshToken;

    static std::vector<std::shared_ptr<MusicObject>> favoriteMusics;
    static std::vector<std::shared_ptr<AuthorObject>> favoriteAuthors;
public:
    User(const User&) = delete;
    void operator=(const User&) = delete;

    static void loadUser(QJsonObject jsonUser);
    static void printInfo();

    static int getId();
    static QString getName();
    static QString getEmail();
    static int getRole();
    static QString getToken();
    static QString getRefreshToken();

    static void setName(QString newName);
    static void setPassword(QString newPassword, QString oldPassword);
    static void setEmail(QString newEmail);
    static void setRole(int newRole);
    static void setToken(QString newToken);
    static void setRefreshToken(QString newRefreshToken);

    static void addMusic(std::shared_ptr<MusicObject> music);
    static void deleteMusic(int musicId);
    static int getMusicsLength();
    static std::shared_ptr<MusicObject> getMusicByInd(int ind);

    static void addAuthor(std::shared_ptr<AuthorObject> author);
    static void deleteAuthor(int authorId);
    static int getAuthorsLength();
    static std::shared_ptr<AuthorObject> getAuthorByInd(int ind);
};

class Author : public User {

};

#endif // USERCLASSES_H
