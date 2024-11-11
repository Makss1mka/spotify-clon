#ifndef HOVERICONBUTTON_H
#define HOVERICONBUTTON_H

#include <QPushButton>
#include <QEnterEvent>
#include <QString>
#include <QWidget>
#include <QEvent>
#include <QIcon>

class HoverIconButton : public QPushButton {
    Q_OBJECT
public:
    HoverIconButton(const QIcon& icon, const QIcon& iconActive);
    virtual ~HoverIconButton() = default;

    void setNewIconPath(const QString &newIconPath);
    void setNewActiveIconPath(const QString &newIconActivePath);
protected:
    virtual void enterEvent(QEnterEvent *event) override;
    virtual void leaveEvent(QEvent *event) override;

    QIcon icon;
    QIcon iconActive;
};

#endif // HOVERICONBUTTON_H
