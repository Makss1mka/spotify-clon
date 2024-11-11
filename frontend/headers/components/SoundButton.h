#ifndef SOUNDBUTTON_H
#define SOUNDBUTTON_H

#include "./HoverIconButton.h"
#include <QEnterEvent>
#include <QString>
#include <QEvent>

class SoundButton : public HoverIconButton {
    Q_OBJECT
public:
    SoundButton();
    virtual ~SoundButton() = default;

    bool isMuted;
    int previousVolumeLevel;

    void swapActiveIcons();
protected:
    virtual void enterEvent(QEnterEvent *event) override;
    virtual void leaveEvent(QEvent *event) override;
};

#endif // SOUNDBUTTON_H
