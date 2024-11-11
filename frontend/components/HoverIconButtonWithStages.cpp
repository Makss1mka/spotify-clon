#include "../headers/components/HoverIconButtonWithStages.h"
#include "../headers/components/HoverIconButton.h"
#include "../headers/utils/globalVariables.h"
#include <QPushButton>
#include <QWidget>
#include <QString>
#include <QEvent>
#include <QIcon>
#include <QEnterEvent>

HoverIconButtonWithStages::HoverIconButtonWithStages(const QIcon& icon, const QIcon& iconActive, const QIcon& iconClicked, const QIcon& iconClickedActive)
    : HoverIconButton(icon, iconActive), iconClicked(iconClicked), iconClickedActive(iconClickedActive) {
    setMouseTracking(true);

    setIcon(QIcon(":/assets/sound.png"));
}

void HoverIconButtonWithStages::swapActiveIcons() {
    if (isMuted == true) {
        setIcon(QIcon(":/assets/no-sound-active.png"));
    } else {
        setIcon(QIcon(":/assets/sound-active.png"));
    }
}

void HoverIconButtonWithStages::enterEvent(QEnterEvent *event) {
    if (isMuted == false) {
        setIcon(QIcon(":/assets/sound-active.png"));
    } else {
        setIcon(QIcon(":/assets/no-sound-active.png"));
    }
    QPushButton::enterEvent(event);
}

void HoverIconButtonWithStages::leaveEvent(QEvent *event) {
    if (isMuted == false) {
        setIcon();
    } else {
        setIcon(QIcon(":/assets/no-sound.png"));
    }
    QPushButton::leaveEvent(event);
}
