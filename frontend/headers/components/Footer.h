#ifndef LITTLEPLAYER_H
#define LITTLEPLAYER_H

#include "./HoverIconButton.h"
#include "./SoundButton.h"
#include <QWidget>
#include <QLabel>
#include <QSlider>
#include <QPushButton>
#include <QTimer>

class Footer : public QWidget {
    Q_OBJECT
public:
    explicit Footer(QWidget *parent = nullptr);
private:
    void updateMusicTimeline();

    HoverIconButton *musicImage;
    QLabel *nameLabel;
    QLabel *authorLabel;
    HoverIconButton *musicConfigButton;

    HoverIconButton *shuffleButton;
    HoverIconButton *backButton;
    QPushButton *stopButton;
    HoverIconButton *nextButton;
    HoverIconButton *repeatButton;
    HoverIconButton* btn;
    QLabel *startTime;
    QLabel *endTime;
    QSlider *musicTimeline;
    QLabel *timelineCircle;

    SoundButton *soundButton;
    QSlider *volumeSlider;

    QTimer *timelineUpdateTimer;
};

#endif // LITTLEPLAYER_H
