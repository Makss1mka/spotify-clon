#include "../headers/utils/UserClasses.h"
#include "../headers/utils/MusicClass.h"

User::User(QJsonObject jsonUser) {

}

QString User::getName() {

}

QString User::getEmail() {

}

int User::getRole() {
    return role;
}

void User::setName(QString newName) {

}

void User::setPassword(QString newPassword, QString oldPassword) {

}

void User::setEmail(QString newEmail) {

}

void User::setRole(int role) {

}

void User::pushMusic(std::shared_ptr<Music>) {

}

void User::deleteMusic(int id) {

}

int User::getMusicsLength() {
    return favoriteMusics.size();
}

std::shared_ptr<Music> User::getMusicByInd(int ind) {
    return favoriteMusics[ind];
}

void User::pushAuthor(std::shared_ptr<Author> author) {
    favoriteAuthors.push_back(author);
}

void User::deleteAuthor(QString authorName) {
    for(int i = 0; i < favoriteAuthors.size(); i++) {
        if (Author.name == authorName) {
            favoriteAuthors.erase(favoriteAuthors.begin() + i);
        }
    }
}

int User::getAuthorsLength() {
    return favoriteAuthors.size();
}

std::shared_ptr<Music> User::getAuthorByInd(int ind) {
    return favoriteAuthors[ind];
}

