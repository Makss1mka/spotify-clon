#ifndef VOLUMESLIDER_H
#define VOLUMESLIDER_H

#include <QMouseEvent>
#include <QSlider>

class VolumeSlider : public QSlider {
    Q_OBJECT
public:
    using QSlider::QSlider;
protected:
    void mousePressEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
};

#endif // VOLUMESLIDER_H
