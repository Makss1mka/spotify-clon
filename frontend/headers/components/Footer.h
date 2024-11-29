#ifndef LITTLEPLAYER_H
#define LITTLEPLAYER_H

#include "./HoverIconButtonWithStages.h"
#include "./HoverIconButton.h"
#include "./VolumeSlider.h"
#include "./MusicSlider.h"
#include "./SoundButton.h"
#include <QPushButton>
#include <QWidget>
#include <QSlider>
#include <QLabel>
#include <QTimer>

class Footer : public QWidget {
    Q_OBJECT
public:
    explicit Footer(QWidget *parent = nullptr);
private:
    QPushButton *musicImage;
    QPushButton *nameLabel;
    QPushButton *authorLabel;

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
signals:
    void trackChanged();
};

#endif // LITTLEPLAYER_H
