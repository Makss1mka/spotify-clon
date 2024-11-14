#ifndef SOUNDBUTTON_H
#define SOUNDBUTTON_H

#include "./HoverIconButtonWithStages.h"

class SoundButton : public HoverIconButtonWithStages {
    Q_OBJECT
public:
    SoundButton();
    virtual ~SoundButton() = default;

    void setPreviousVolumeLevel(int previousVolumeLevel);
    int getPreviousVolumeLevel();
protected:
    int previousVolumeLevel;
};

#endif // SOUNDBUTTON_H
