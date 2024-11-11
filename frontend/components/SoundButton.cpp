#include "../headers/components/HoverIconButton.h"
#include "../headers/components/SoundButton.h"
#include "../headers/utils/globalVariables.h"
#include <QPushButton>
#include <QWidget>
#include <QString>
#include <QEvent>
#include <QIcon>
#include <QEnterEvent>

SoundButton::SoundButton()
    : HoverIconButton("", "") {
    setMouseTracking(true);

    previousVolumeLevel = Globals::player->getVolumeLevel();
    isMuted = false;
    setIcon(QIcon(":/assets/sound.png"));
}

void SoundButton::swapActiveIcons() {
    if (isMuted == true) {
        setIcon(QIcon(":/assets/no-sound-active.png"));
    } else {
        setIcon(QIcon(":/assets/sound-active.png"));
    }
}

void SoundButton::enterEvent(QEnterEvent *event) {
    if (isMuted == false) {
        setIcon(QIcon(":/assets/sound-active.png"));
    } else {
        setIcon(QIcon(":/assets/no-sound-active.png"));
    }
    QPushButton::enterEvent(event);
}

void SoundButton::leaveEvent(QEvent *event) {
    if (isMuted == false) {
        setIcon(QIcon(":/assets/sound.png"));
    } else {
        setIcon(QIcon(":/assets/no-sound.png"));
    }
    QPushButton::leaveEvent(event);
}
