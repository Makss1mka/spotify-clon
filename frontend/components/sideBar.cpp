#include "../headers/components/SideBar.h"
#include <QPushButton>
#include <QVBoxLayout>
#include <QSizePolicy>

SideBar::SideBar(QWidget *parent) : QWidget(parent) {
    QWidget* mainWidget = new QWidget(this);
    mainWidget->setStyleSheet("background: #A5A5A5; border-radius: 20px; height: 100%; width: 270px; ");
    mainWidget->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    QVBoxLayout* mainLayout = new QVBoxLayout;
    mainLayout->addWidget(new QPushButton("POPA"));
    mainLayout->addStretch();

    mainWidget->setLayout(mainLayout);
}

