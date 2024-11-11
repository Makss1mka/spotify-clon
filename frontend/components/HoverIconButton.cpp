#include "../headers/components/HoverIconButton.h"
#include <QPushButton>
#include <QWidget>
#include <QString>
#include <QEvent>
#include <QIcon>
#include <QEnterEvent>

HoverIconButton::HoverIconButton(const QIcon& icon, const QIcon& iconActive)
    : QPushButton(nullptr), iconPath(icon), iconActivePath(iconActive) {
    setMouseTracking(true);
    setIcon(iconPath);
}

void HoverIconButton::enterEvent(QEnterEvent *event) {
    setIcon(this->iconActivePath);
    QPushButton::enterEvent(event);
}

void HoverIconButton::leaveEvent(QEvent *event) {
    setIcon(this->iconPath);
    QPushButton::leaveEvent(event);
}

void HoverIconButton::setNewActiveIconPath(const QString &newIconActivePath) {
    iconActivePath = newIconActivePath;
}

void HoverIconButton::setNewIconPath(const QString &newIconPath) {
    iconPath = newIconPath;
}
