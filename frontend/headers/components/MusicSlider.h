#ifndef MUSICSLIDER_H
#define MUSICSLIDER_H

#include <QMouseEvent>
#include <QSlider>
#include <QTimer>

class MusicSlider : public QSlider {
    Q_OBJECT
public:
    explicit MusicSlider(QWidget *parent = nullptr);
protected:
    void mousePressEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;

    QTimer* timer;
signals:
    void secondChanged(int value);
};

#endif // MUSICSLIDER_H
