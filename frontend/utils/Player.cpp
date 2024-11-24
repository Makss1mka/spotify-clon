#include "../headers/utils/MusicClass.h"
#include "../headers/utils/HttpClient.h"
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
    checkTimer = new QTimer();
    musicBuffer = new char[1];

    checkTimer->connect(checkTimer, &QTimer::timeout, this, &Player::checkStatus);
    connect(this, &Player::playbackFinished, [this](){
        if(isRepeated == false) {
            next();
        } else {
            setPosition(0);
        }
    });

    HttpClient::sendGetRequest(QUrl("http://localhost:3000/admin/getAllMusicInfo"), [this](HttpClient::Response* response){
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
    if (position >= 0 && position <= 100) {
        music.setPlayingOffset(sf::milliseconds(static_cast<float>(musicQueue[currentQueueInd]->getDuration() * position * 10)));
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

    loadTrack(QUrl("http://localhost:3000/music/getAudio?path=" + musicQueue[currentQueueInd]->getPath()));

    if (isPaused) music.pause();

    emit trackChanged();

    return true;
    // логика по добавлению новых
}

bool Player::prev() {
    if (currentQueueInd <= 0) return false;

    currentQueueInd--;

    loadTrack(QUrl("http://localhost:3000/music/getAudio?path=" + musicQueue[currentQueueInd]->getPath()));

    if (isPaused == true) music.pause();

    emit trackChanged();

    return true;
}

void Player::pause() {
    if (isCurrentLoaded == false) return;

    isPaused = true;

    music.pause();
}

void Player::play() {
    if (isCurrentLoaded == false) {
        //player->setSource(QUrl("http://localhost:3000/music/getFile?path=" + musicQueue[currentQueueInd]->getPath()));
        isCurrentLoaded = true;
    }
    //player->play();
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
    return musicQueue[currentQueueInd];
}

void Player::loadTrack(QUrl url) {
    HttpClient::sendGetRequest(url, [this](HttpClient::Response* response){
        if(response->statusCode < 400) {
            checkTimer->stop();
            music.stop();

            musicBuffer = response->body.data();
            bufferLength = response->body.size();

            if(music.openFromMemory(musicBuffer, bufferLength)) music.play();

            checkTimer->start(100);
        }
    });
}

void Player::checkStatus() {
    if (music.getStatus() == sf::SoundSource::Stopped) {
        checkTimer->stop();
        emit playbackFinished();
    }
}
