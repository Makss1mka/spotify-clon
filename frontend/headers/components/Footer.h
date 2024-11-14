#ifndef LITTLEPLAYER_H
#define LITTLEPLAYER_H

#include "./HoverIconButtonWithStages.h"
#include "./HoverIconButton.h"
#include "./VolumeSlider.h"
#include "./MusicSlider.h"
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
    HoverIconButton *musicImage;
    QLabel *nameLabel;
    QLabel *authorLabel;

    HoverIconButtonWithStages *shuffleButton;
    HoverIconButton *backButton;
    QPushButton *stopButton;
    HoverIconButton *nextButton;
    HoverIconButtonWithStages *repeatButton;
    HoverIconButton* btn;
    QLabel *startTime;
    QLabel *endTime;
    MusicSlider *musicTimeline;
    QLabel *timelineCircle;

    SoundButton *soundButton;
    VolumeSlider *volumeSlider;

    QTimer *timelineUpdateTimer;
};

#endif // LITTLEPLAYER_H
