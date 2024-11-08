#include "../headers/components/SideBar.h"
#include <QPushButton>
#include <QVBoxLayout>
#include <QSizePolicy>

SideBar::SideBar(QWidget *parent) : QWidget(parent) {
    this->setStyleSheet("backround: #A5A5A5; border-radius: 20px; ");
    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
}

