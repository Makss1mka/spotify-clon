#ifndef HOVERICONBUTTONWITHSTAGES_H
#define HOVERICONBUTTONWITHSTAGES_H

#include "./HoverIconButton.h"
#include <QEnterEvent>
#include <QEvent>
#include <QIcon>

class HoverIconButtonWithStages : public HoverIconButton {
    Q_OBJECT
public:
    HoverIconButtonWithStages(const QIcon& icon, const QIcon& iconActive, const QIcon& iconClicked, const QIcon& iconClickedActive);
    virtual ~HoverIconButtonWithStages() = default;

    bool isButtonClicked();
    void swapStage();
    void swapActiveIcons();
protected:
    virtual void enterEvent(QEnterEvent *event) override;
    virtual void leaveEvent(QEvent *event) override;

    bool isClicked;
    QIcon iconClicked;
    QIcon iconClickedActive;
};

#endif // HOVERICONBUTTONWITHSTAGES_H
