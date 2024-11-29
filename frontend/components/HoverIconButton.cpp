#include "../headers/components/HoverIconButton.h"
#include <QEnterEvent>
#include <QPushButton>
#include <QWidget>
#include <QString>
#include <QEvent>
#include <QIcon>

HoverIconButton::HoverIconButton(const QIcon& icon, const QIcon& iconActive)
    : QPushButton(nullptr), icon(icon), iconActive(iconActive) {
    setMouseTracking(true);
    setIcon(icon);
}

void HoverIconButton::enterEvent(QEnterEvent *event) {
    setIcon(this->iconActive);
    setCursor(Qt::PointingHandCursor);
    QPushButton::enterEvent(event);
}

void HoverIconButton::leaveEvent(QEvent *event) {
    setIcon(this->icon);
    unsetCursor();
    QPushButton::leaveEvent(event);
}

void HoverIconButton::setNewActiveIconPath(const QIcon& newIconActive) {
    iconActive = newIconActive;
}

void HoverIconButton::setNewIconPath(const QIcon& newIcon) {
    icon = newIcon;
}
