#include "../headers/utils/globalVariables.h"
#include "../headers/utils/MusicClass.h"
#include "../headers/utils/HttpClient.h"
#include "../headers/utils/Player.h"
#include <QMediaPlayer>
#include <QAudioOutput>
#include <QJsonObject>
#include <QByteArray>
#include <QObject>
#include <QBuffer>
#include <QUrl>

Player::Player() : QObject(nullptr) {
    isQueueFree = true;
    isPaused = true;
    currentQueueInd = -1;
    isCurrentLoaded = false;
    volumeLevel = 50;
    isRepeated = false;

    player = new QMediaPlayer();
    player->pause();
    outputDevice = new QAudioOutput();
    outputDevice->setVolume(50);
    player->setAudioOutput(outputDevice);

    player->connect(player, &QMediaPlayer::mediaStatusChanged, this, [this](QMediaPlayer::MediaStatus status){
        qDebug() << "Popa" << status;
        if (status == QMediaPlayer::EndOfMedia) {
            qDebug() << "Popa 2";
            if(isRepeated == false) {
                qDebug() << "Popa 3";
                next();
            } else {
                qDebug() << "Popa 4";
                setPosition(0);
            }
        }
    });

    Globals::httpClient->sendGetRequest(QUrl("http://localhost:3000/admin/getAllMusicInfo"), [this](const HttpClient::Response& response){
        std::vector<std::shared_ptr<Music>> musics;
        for(int i = 0; i < response.bodyJsonArray.size(); i++) {
            musics.push_back(std::make_shared<Music>(response.bodyJsonArray[i].toObject()));
            qDebug() << response.bodyJsonArray[i].toObject();
        }
        this->setPlaylist(musics);
        this->next();
        this->pause();
    });
}

void Player::setPlaylist(std::vector<std::shared_ptr<Music>>& music) {
    if (music.size() > 0) {
        musicQueue = music;
        isQueueFree = false;
        isCurrentLoaded = false;
        currentQueueInd = 0;
    }
}

void Player::pushInTheEndMusic(std::shared_ptr<Music> music) {
    this->musicQueue.push_back(music);
}

void Player::pushNextMusic(std::shared_ptr<Music> music) {
    this->musicQueue.insert(this->musicQueue.begin() + currentQueueInd + 1, music);
}

void Player::popMusic() {
    this->musicQueue.erase(this->musicQueue.begin());
}

void Player::setVolumeLevel(int value) {
    if (value >= 0 && value <= 100) {
        outputDevice->setVolume(value);
        volumeLevel = value;
    }
}

void Player::setPosition(int position) {
    player->setPosition(position);
}

void Player::clearQueue() {
    musicQueue.clear();

    currentQueueInd == -1;
    isPaused = true;
    isQueueFree = true;
    isCurrentLoaded = false;
}

void Player::next() {
    if (currentQueueInd > musicQueue.size()) return;

    currentQueueInd++;

    player->setSource(QUrl("http://localhost:3000/music/getFile?path=" + musicQueue[currentQueueInd]->getPath()));

    player->play();
    isPaused = false;
    isCurrentLoaded = true;

    if(currentQueueInd > 7) popMusic();

    // логика по добавлению новых
}

void Player::prev() {
    if (currentQueueInd <= 0) return;

    currentQueueInd--;

    player->setSource(QUrl("http://localhost:3000/music/getFile?path=" + musicQueue[currentQueueInd]->getPath()));

    player->play();
    isPaused = false;
    isCurrentLoaded = true;
}

void Player::pause() {
    if (isCurrentLoaded == false) return;

    player->pause();
    isPaused = true;
}

void Player::play() {
    if (isCurrentLoaded == false) {
        player->setSource(QUrl("http://localhost:3000/music/getFile?path=" + musicQueue[currentQueueInd]->getPath()));
        isCurrentLoaded = true;
    }
    player->play();
    isPaused = false;
}

bool Player::isPlayerPaused() {
    return isPaused;
}

int Player::getVolumeLevel() {
    return volumeLevel;
}

bool Player::isOnRepeat() {
    return isRepeated;
}

void Player::swapRepeating() {
    isRepeated = !isRepeated;
}
