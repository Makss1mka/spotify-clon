#include "../headers/components/HoverIconButtonWithStages.h"
#include "../headers/components/SoundButton.h"
#include "../headers/utils/globalVariables.h"
#include <QPushButton>
#include <QWidget>
#include <QString>
#include <QEvent>
#include <QIcon>
#include <QEnterEvent>

SoundButton::SoundButton()
    : HoverIconButtonWithStages(QIcon(":/assets/sound.png"), QIcon(":/assets/sound-active.png"),
        QIcon(":/assets/no-sound.png"), QIcon(":/assets/no-sound-active.png")) {}

void SoundButton::setPreviousVolumeLevel(int previousVolumeLevel) {
    this->previousVolumeLevel = previousVolumeLevel;
}

int SoundButton::getPreviousVolumeLevel() {
    return previousVolumeLevel;
}
