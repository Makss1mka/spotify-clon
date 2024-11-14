#ifndef USERCLASSES_H
#define USERCLASSES_H

#include "./MusicClass.h"
#include <QJsonObject>
#include <QString>
#include <vector>

class User {
public:
    User(QJsonObject jsonUser);

    QString getName();
    QString getEmail();
    int getRole();

    void setName(QString newName);
    void setPassword(QString newPassword, QString oldPassword);
    void setEmail(QString newEmail);
    void setRole(int role);

    void pushMusic(std::shared_ptr<Music>);
    void deleteMusic(int id);
    int getMusicsLength();
    std::shared_ptr<Music> getMusicByInd(int ind);

    void pushAuthor(std::shared_ptr<Music>);
    void deleteAuthor(int id);
    int getAuthorsLength();
    std::shared_ptr<Music> getAuthorByInd(int ind);
protected:
    QString name;
    QString password;
    QString email;
    int role;

    std::vector<std::shared_ptr<Music>> favoriteMusics;
    std::vector<std::shared_ptr<Author>> favoriteAuthors;
};

class Author : public User {

};

#endif // USERCLASSES_H
