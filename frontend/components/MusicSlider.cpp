#include "../headers/components/MusicSlider.h"
#include "../headers/utils/globalVariables.h"
#include <QStyleOptionSlider>
#include <QMouseEvent>
#include <QSlider>
#include <QTimer>
#include <QStyle>

MusicSlider::MusicSlider(QWidget *parent) : QSlider(Qt::Horizontal, parent) {
    timer = new QTimer();

    timer->connect(timer, &QTimer::timeout, [this](){
        if (Globals::player->isPlayerPaused() == false) {
            this->setValue(this->value() + 1);
            if(this->value() % 100 == 0) {
                emit secondChanged(this->value());
            }
        }
    });
    timer->start(10);
}

void MusicSlider::mousePressEvent(QMouseEvent* event) {
    if (event->button() == Qt::LeftButton) {
        // Инициализация объекта QStyleOptionSlider текущими параметрами слайдера
        QStyleOptionSlider opt;
        initStyleOption(&opt);

        // Получаем размер и положение канавки слайдера
        QRect sliderGroove = style()->subControlRect(QStyle::CC_Slider, &opt, QStyle::SC_SliderGroove, this);

        if (sliderGroove.contains(event->pos())) {
            int sliderMin = sliderGroove.x();
            int sliderMax = sliderGroove.right();
            int newValue = minimum() + (maximum() - minimum()) * (event->pos().x() - sliderMin) / (sliderMax - sliderMin);

            setValue(newValue);
            emit secondChanged(newValue);
            Globals::player->setPosition(newValue);
            event->accept();

            return;
        }
    }
    QSlider::mousePressEvent(event);
}

void MusicSlider::mouseMoveEvent(QMouseEvent* event) {
    if (event->buttons() & Qt::LeftButton) {
        QStyleOptionSlider opt;
        initStyleOption(&opt);

        QRect sliderGroove = style()->subControlRect(QStyle::CC_Slider, &opt, QStyle::SC_SliderGroove, this);

        if (sliderGroove.contains(event->pos())) {
            int sliderMin = sliderGroove.x();
            int sliderMax = sliderGroove.right();
            int newValue = minimum() + (maximum() - minimum()) * (event->pos().x() - sliderMin) / (sliderMax - sliderMin);

            setValue(newValue);
            emit secondChanged(newValue);
            Globals::player->setPosition(newValue);
            event->accept();

            return;
        }
    }
    QSlider::mouseMoveEvent(event);
}

void MusicSlider::mouseReleaseEvent(QMouseEvent* event) {
    if (event->button() == Qt::LeftButton) {
        event->accept();
    }
    QSlider::mouseReleaseEvent(event);
}


