#include "../headers/utils/UserClasses.h"
#include "../headers/utils/MusicClass.h"
#include "../headers/utils/HttpClient.h"
#include "../headers/utils/EnvFile.h"
#include "../headers/utils/Player.h"
#include <SFML/Audio.hpp>
#include <QMediaPlayer>
#include <QAudioOutput>
#include <QJsonObject>
#include <QByteArray>
#include <QObject>
#include <QBuffer>
#include <QTimer>
#include <QUrl>

Player::Player() : QObject(nullptr) {
    isCurrentLoaded = false;
    isQueueFree = true;
    isPaused = true;
    isRepeated = false;
    currentQueueInd = -1;
    volumeLevel = 100;

    //deviceCheckTimer = new QTimer();
    //deviceCheckTimer->connect(deviceCheckTimer, &QTimer::timeout, this, &Player::checkDevices);
    checkTimer = new QTimer();
    checkTimer->connect(checkTimer, &QTimer::timeout, this, &Player::checkStatus);
    connect(this, &Player::playbackFinished, [this](){
        if(isRepeated == false) {
            next();
        } else {
            loadTrackFromBuffer();
            emit trackChanged();
        }
    });

    HttpClient::sendGetRequest(QUrl(Env::get("SERVER_DOMEN") + "/user/getFavMusic?user_id=" + QString::number(User::getId())), [this](HttpClient::Response* response){
        std::vector<std::shared_ptr<MusicObject>> musics;
        for(int i = 0; i < response->bodyJsonArray.size(); i++) {
            musics.push_back(std::make_shared<MusicObject>(response->bodyJsonArray[i].toObject()));
        }
        setPlaylist(musics);
    });
}

void Player::setPlaylist(std::vector<std::shared_ptr<MusicObject>>& music) {
    if (music.size() > 0) {
        musicQueue = music;
        isQueueFree = false;
        isCurrentLoaded = true;
        currentQueueInd = 0;
        loadTrack(QUrl(Env::get("SERVER_DOMEN") + "/music/getAudio?path=" + musicQueue[currentQueueInd]->getPath()));
        emit trackChanged();
    }
}

void Player::pushInTheEndMusic(std::shared_ptr<MusicObject> music) {
    musicQueue.push_back(music);
}

void Player::pushNextMusic(std::shared_ptr<MusicObject> music) {
    musicQueue.insert(musicQueue.begin() + currentQueueInd + 1, music);
}

void Player::popMusic() {
    musicQueue.erase(musicQueue.begin());
}

void Player::setVolumeLevel(int value) {
    if (value >= 0 && value <= 100) {
        music.setVolume(static_cast<float>(value));
    }
}

void Player::setPosition(int position) {
    if (position >= 0 && position <= musicQueue[currentQueueInd]->getDuration() * 1000) {
        music.setPlayingOffset(sf::milliseconds(position * 10));
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

    loadTrack(QUrl(Env::get("SERVER_DOMEN") + "/music/getAudio?path=" + musicQueue[currentQueueInd]->getPath()));

    emit trackChanged();

    if (currentQueueInd >= musicQueue.size() - 3) {
        HttpClient::sendGetRequest(
            QUrl(Env::get("SERVER_DOMEN") +
                 "/music/recomend?janre=" + this->musicQueue[this->currentQueueInd + 2]->getJanres().mid(0, this->musicQueue[this->currentQueueInd + 2]->getJanres().size() - 1) +
                 "&author=" + this->musicQueue[this->currentQueueInd + 2]->getAuthor() +
                 "&lang=" + this->musicQueue[this->currentQueueInd + 2]->getLang() +
                 "&track_name=" + this->musicQueue[this->currentQueueInd + 2]->getName() +
                 "&limit=10"),
            [this](HttpClient::Response* response){
            if(response->statusCode < 400) {
                QJsonArray loadedMusic = response->bodyJsonArray;
                for(int i = 0; i < loadedMusic.size(); i++) {
                    this->musicQueue.push_back(std::make_shared<MusicObject>(loadedMusic[i].toObject()));
                }
            }
        });
    }

    return true;
}

bool Player::prev() {
    if (currentQueueInd <= 0) return false;

    currentQueueInd--;

    loadTrack(QUrl(Env::get("SERVER_DOMEN") + "/music/getAudio?path=" + musicQueue[currentQueueInd]->getPath()));

    emit trackChanged();

    return true;
}

void Player::pause() {
    if (isCurrentLoaded == false) return;

    isPaused = true;

    music.pause();
}

void Player::play() {
    if (isCurrentLoaded == false) return;

    isPaused = false;

    music.play();
}

bool Player::isPlayerPaused() {
    return isPaused;
}

bool Player::isCurrentTrackLoaded() {
    return isCurrentLoaded;
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
    if (currentQueueInd >= 0 || currentQueueInd < musicQueue.size()) return musicQueue[currentQueueInd];
}

int Player::getCurrentQueueInd() {
    return currentQueueInd;
}

void Player::loadTrack(QUrl url) {
    HttpClient::sendGetRequest(url, [this](HttpClient::Response* response){
        if(response->statusCode < 400) {
            checkTimer->stop();

            musicBuffer = response->body.data();
            bufferLength = response->body.size();

            if(music.openFromMemory(musicBuffer, bufferLength)) {
                music.play();
                if (this->isPaused == true) music.pause();

                isCurrentLoaded = true;
                checkTimer->start(100);
            }
        }
    });
}

void Player::loadTrackFromBuffer() {
    checkTimer->stop();

    if(music.openFromMemory(musicBuffer, bufferLength)) {
        music.play();
        if (this->isPaused == true) music.pause();

        isCurrentLoaded = true;
        checkTimer->start(100);
    }
}

void Player::checkStatus() {
    if (music.getStatus() == sf::SoundSource::Stopped) {
        checkTimer->stop();
        emit playbackFinished();
    }
}

void Player::checkDevices() {

}

