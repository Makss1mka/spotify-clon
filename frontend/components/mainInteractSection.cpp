#include "../headers/components/MainInteractSection.h"

MainInteractSection::MainInteractSection(QWidget *parent) : QWidget(parent) {
    this->setStyleSheet("backround: #A5A5A5; border-radius: 20px; ");
    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
}
