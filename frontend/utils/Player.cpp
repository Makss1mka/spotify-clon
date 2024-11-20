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
    volumeLevel = 100;
    isRepeated = false;

    player = new QMediaPlayer();
    player->pause();
    outputDevice = new QAudioOutput();
    outputDevice->setVolume(volumeLevel);
    player->setAudioOutput(outputDevice);

    player->connect(player, &QMediaPlayer::mediaStatusChanged, this, [this](QMediaPlayer::MediaStatus status){
        if (status == QMediaPlayer::EndOfMedia) {
            if(isRepeated == false) {
                next();
            } else {
                setPosition(0);
            }
        }
    });

    Globals::httpClient->sendGetRequest(QUrl("http://localhost:3000/admin/getAllMusicInfo"), [this](const HttpClient::Response& response){
        std::vector<std::shared_ptr<MusicObject>> musics;
        for(int i = 0; i < response.bodyJsonArray.size(); i++) {
            musics.push_back(std::make_shared<MusicObject>(response.bodyJsonArray[i].toObject()));
        }
        this->setPlaylist(musics);
    });
}

void Player::setPlaylist(std::vector<std::shared_ptr<MusicObject>>& music) {
    if (music.size() > 0) {
        musicQueue = music;
        isQueueFree = false;
        isCurrentLoaded = false;
        currentQueueInd = 0;
        emit trackChanged();
    }
}

void Player::pushInTheEndMusic(std::shared_ptr<MusicObject> music) {
    this->musicQueue.push_back(music);
}

void Player::pushNextMusic(std::shared_ptr<MusicObject> music) {
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
    if (position >= 0 && position <= 100) {
        qint64 qPosition = static_cast<qint64>(musicQueue[currentQueueInd]->getDuration() * position * 10);

        player->setPosition(qPosition);
    }
}

void Player::clearQueue() {
    musicQueue.clear();

    currentQueueInd == -1;
    isPaused = true;
    isQueueFree = true;
    isCurrentLoaded = false;
}

bool Player::next() {
    if (currentQueueInd + 1 >= musicQueue.size()) return false;

    if(currentQueueInd > 5) {
        popMusic();
    } else {
        currentQueueInd++;
    }

    player->setSource(QUrl("http://localhost:3000/music/getFile?path=" + musicQueue[currentQueueInd]->getPath()));

    if (isPaused == false) play();

    emit trackChanged();
    return true;
    // логика по добавлению новых
}

bool Player::prev() {
    if (currentQueueInd <= 0) return false;

    currentQueueInd--;

    player->setSource(QUrl("http://localhost:3000/music/getFile?path=" + musicQueue[currentQueueInd]->getPath()));

    if (isPaused == false) play();

    emit trackChanged();
    return true;
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

std::shared_ptr<MusicObject> Player::getCurrentMusic() {
    return musicQueue[currentQueueInd];
}

std::shared_ptr<MusicObject> Player::test() {
    return musicQueue[6];
}

