#include "../headers/components/VolumeSlider.h"
#include "../headers/utils/globalVariables.h"
#include <QMouseEvent>
#include <QStyleOptionSlider>
#include <QStyle>
#include <QSlider>

void VolumeSlider::mousePressEvent(QMouseEvent* event) {
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
            Globals::player->setVolumeLevel(newValue);
            event->accept();

            qDebug() << newValue;
            return;
        }
    }
    QSlider::mousePressEvent(event);
}

void VolumeSlider::mouseMoveEvent(QMouseEvent* event) {
    if (event->buttons() & Qt::LeftButton) {
        QStyleOptionSlider opt;
        initStyleOption(&opt);

        QRect sliderGroove = style()->subControlRect(QStyle::CC_Slider, &opt, QStyle::SC_SliderGroove, this);

        if (sliderGroove.contains(event->pos())) {
            int sliderMin = sliderGroove.x();
            int sliderMax = sliderGroove.right();
            int newValue = minimum() + (maximum() - minimum()) * (event->pos().x() - sliderMin) / (sliderMax - sliderMin);

            setValue(newValue);
            Globals::player->setVolumeLevel(newValue);
            event->accept();

            return;
        }
    }
    QSlider::mouseMoveEvent(event);
}

void VolumeSlider::mouseReleaseEvent(QMouseEvent* event) {
    if (event->button() == Qt::LeftButton) {
        event->accept();
    }
    QSlider::mouseReleaseEvent(event);
}
