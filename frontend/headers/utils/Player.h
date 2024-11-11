#ifndef PLAYER_H
#define PLAYER_H

#include "./MusicClass.h"
#include <QMediaPlayer>
#include <QAudioOutput>
#include <QByteArray>
#include <vector>
#include <QObject>

class Player : public QObject {
    Q_OBJECT
public:
    Player();

    void pushInTheEndMusic(std::shared_ptr<Music> music);
    void pushNextMusic(std::shared_ptr<Music> music);
    void popMusic();
    void clearQueue();
    void setPlaylist(std::vector<std::shared_ptr<Music>>& music);

    void setVolumeLevel(int value);
    void setPosition(int position);
    void next();
    void prev();
    void pause();
    void play();
    bool isPlayerPaused();
    int getVolumeLevel();
    bool isOnRepeat();
    void swapRepeating();
private:
    bool isCurrentLoaded;
    bool isQueueFree;
    QMediaPlayer* player;
    bool isPaused;
    int currentQueueInd;
    int volumeLevel;
    bool isRepeated;
    QAudioOutput* outputDevice;

    std::vector<std::shared_ptr<Music>> musicQueue;
};

#endif // PLAYER_H
