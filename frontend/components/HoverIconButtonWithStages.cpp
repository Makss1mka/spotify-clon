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

    isClicked = false;
    setIcon(icon);
}

bool HoverIconButtonWithStages::isButtonClicked() {
    return isClicked;
}

void HoverIconButtonWithStages::swapStage() {
    isClicked = !isClicked;

    if (isClicked == true) {
        setIcon(iconClickedActive);
    } else {
        setIcon(iconActive);
    }
}

void HoverIconButtonWithStages::enterEvent(QEnterEvent *event) {
    if (isClicked == false) {
        setIcon(iconActive);
    } else {
        setIcon(iconClickedActive);
    }
    setCursor(Qt::PointingHandCursor);
    QPushButton::enterEvent(event);
}

void HoverIconButtonWithStages::leaveEvent(QEvent *event) {
    if (isClicked == false) {
        setIcon(icon);
    } else {
        setIcon(iconClicked);
    }
    unsetCursor();
    QPushButton::leaveEvent(event);
}
