#include "../headers/utils/UserClasses.h"
#include "../headers/utils/MusicClass.h"
#include "../headers/utils/EnvFile.h"
#include "../headers/utils/HttpClient.h"
#include <QJsonObject>
#include <QString>
#include <QUrl>

int User::id = 1;
QString User::name = "";
QString User::email = "";
QString User::password = "";
int User::role = 0;
std::vector<std::shared_ptr<AuthorObject>> User::favoriteAuthors;
std::vector<std::shared_ptr<MusicObject>> User::favoriteMusics;
User::User() {}

void User::loadUser(QJsonObject userObj) {
    id = userObj.value("id").toInt();
    name = userObj.value("login").toString();
    email = userObj.value("email").toString();
    role = userObj.value("role").toInt();

    for(int i = 0; i < userObj.value("favMusics").toArray().size(); i++) {
        favoriteMusics.push_back(std::make_shared<MusicObject>(userObj.value("favMusics")[i].toObject()));
    }

    for(int i = 0; i < userObj.value("favAuthors").toArray().size(); i++) {
        favoriteAuthors.push_back(std::make_shared<AuthorObject>(userObj.value("favAuthors")[i].toObject()));
    }

    printInfo();
}

void User::printInfo() {
    qDebug() << "id: " << id;
    qDebug() << "login: " << name;
    qDebug() << "email: " << email;
    qDebug() << "role: " << role;

    for(auto& music : favoriteMusics) {
        qDebug() << "Music: id - " << music->getId()
            << " name - " << music->getName()
            << " author - " << music->getAuthor()
            << " author-id - " << music->getAuthorId()
            << " dur - " << music->getDuration()
            << " path - " << music->getPath()
            << " listens - " << music->getListens()
            << " janres - " << music->getJanres()
            << " lang - " << music->getLang();
    }

    for(auto& author : favoriteAuthors) {
        qDebug() << "author: id - " << author->getId()
            << " name -  " << author->getName();
    }

}

int User::getId() {
    return id;
}

QString User::getName() {
    return name;
}

QString User::getEmail() {
    return email;
}

int User::getRole() {
    return role;
}

void User::setName(QString newName) {
    name = newName;
}

void User::setEmail(QString newEmail) {
    email = newEmail;
}

void User::setRole(int newRole) {
    role = newRole;
}

void User::addMusic(std::shared_ptr<MusicObject> music) {
    for(int i = 0; i < favoriteMusics.size(); i++) {
        if (music->getId() == favoriteMusics[i]->getId()) return;
    }
    favoriteMusics.push_back(music);

    QJsonObject body;
    body["music_id"] = music->getId();
    body["user_id"] = id;

    HttpClient::sendPostRequest(QUrl(Env::get("SERVER_DOMEN", ":/.env") + "/user/addFavMusic"), body, [favoriteMusics, music](HttpClient::Response* response){

    });
}

void User::deleteMusic(int musicId) {
    for(int i = 0; i < favoriteMusics.size(); i++) {
        if (musicId == favoriteMusics[i]->getId()) {
            favoriteMusics.erase(favoriteMusics.begin() + i);
            return;
        }
    }
    HttpClient::sendDeleteRequest(QUrl(Env::get("SERVER_DOMEN", ":/.env") + "/user/delFavMusic?user_id=" + QString::number(User::getId()) + "&music_id=" + QString::number(musicId)),
        [favoriteMusics, musicId](HttpClient::Response* response){

    });
}

int User::getMusicsLength() {
    return favoriteMusics.size();
}

std::shared_ptr<MusicObject> User::getMusicByInd(int ind) {
    return favoriteMusics[ind];
}

void User::addAuthor(std::shared_ptr<AuthorObject> author) {
    for(int i = 0; i < favoriteAuthors.size(); i++) {
        if (author->getId() == favoriteAuthors[i]->getId()) return;
    }
    favoriteAuthors.push_back(author);

    QJsonObject body;
    body["author_id"] = author->getId();
    body["user_id"] = id;

    HttpClient::sendPostRequest(QUrl(Env::get("SERVER_DOMEN", ":/.env") + "/user/addFavAuthor"), body, [favoriteAuthors, author](HttpClient::Response* response){

    });
}

void User::deleteAuthor(int authorId) {
    for(int i = 0; i < favoriteAuthors.size(); i++) {
        if (authorId == favoriteAuthors[i]->getId()) {
            favoriteAuthors.erase(favoriteAuthors.begin() + i);
            return;
        }
    }

    HttpClient::sendDeleteRequest(QUrl(Env::get("SERVER_DOMEN", ":/.env") + "/user/delFavAuthor?user_id=" + QString::number(User::getId()) + "&author_id=" + QString::number(authorId)),
        [favoriteAuthors, authorId](HttpClient::Response* response){

    });
}

int User::getAuthorsLength() {
    return User::favoriteAuthors.size();
}

std::shared_ptr<AuthorObject> User::getAuthorByInd(int ind) {
    return User::favoriteAuthors[ind];
}

