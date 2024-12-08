#ifndef PLAYER_H
#define PLAYER_H

#include "./MusicClass.h"
#include <SFML/Audio.hpp>
#include <QMediaPlayer>
#include <QAudioOutput>
#include <QByteArray>
#include <QObject>
#include <QTimer>
#include <vector>
#include <QUrl>

class Player : public QObject {
    Q_OBJECT
public:
    Player();

    void pushInTheEndMusic(std::shared_ptr<MusicObject> music);
    void pushNextMusic(std::shared_ptr<MusicObject> music);
    void popMusic();
    void clearQueue();
    void setPlaylist(std::vector<std::shared_ptr<MusicObject>>& music);
    std::shared_ptr<MusicObject> getCurrentMusic();

    void setVolumeLevel(int value);
    void setPosition(int position);
    bool next();
    bool prev();
    void pause();
    void play();
    void stop();
    bool isPlayerPaused();
    bool isCurrentTrackLoaded();
    int getVolumeLevel();
    int getCurrentQueueInd();
    bool isOnRepeat();
    void swapRepeating();
    int getDuration() {
        return static_cast<int>(music.getDuration().asSeconds());
    }
private:
    void loadTrack(QUrl);
    void loadTrackFromBuffer();

    sf::Music music;
    QTimer* checkTimer;
    char* musicBuffer;
    int bufferLength;
    std::vector<std::shared_ptr<MusicObject>> musicQueue;

    bool isCurrentLoaded;
    bool isQueueFree;
    bool isPaused;
    bool isRepeated;
    int currentQueueInd;
    int volumeLevel;
signals:
    void playbackFinished();
    void playbackError();
    void trackChanged();
private slots:
    void checkStatus();
    void checkDevices();
};

#endif // PLAYER_H
