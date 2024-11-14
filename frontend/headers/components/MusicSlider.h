#ifndef MUSICSLIDER_H
#define MUSICSLIDER_H

#include <QMouseEvent>
#include <QSlider>

class MusicSlider : public QSlider {
    Q_OBJECT
public:
    using QSlider::QSlider;
protected:
    void mousePressEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
};

#endif // MUSICSLIDER_H
