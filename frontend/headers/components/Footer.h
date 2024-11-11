#ifndef LITTLEPLAYER_H
#define LITTLEPLAYER_H

#include <QWidget>
#include <QLabel>
#include <QSlider>
#include <QPushButton>
#include <QTimer>

class Player : public QWidget {
    Q_OBJECT
public:
    explicit Player(QWidget *parent = nullptr);
private:
    void updateMusicTimeline();

    QPushButton *musicImage;
    QLabel *nameLabel;
    QLabel *authorLabel;
    QPushButton *musicConfigButton;

    QPushButton *shuffleButton;
    QPushButton *backButton;
    QPushButton *stopButton;
    QPushButton *nextButton;
    QPushButton *repeatButton;
    QLabel *startTime;
    QLabel *endTime;
    QSlider *musicTimeline;
    QLabel *timelineCircle;

    QPushButton *soundButton;
    QSlider *volumeSlider;

    QTimer *timelineUpdateTimer;
};

#endif // LITTLEPLAYER_H
