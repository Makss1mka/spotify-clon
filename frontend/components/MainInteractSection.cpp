#include "../headers/components/MainInteractSection.h"
#include <QVBoxLayout>

MainInteractSection::MainInteractSection(QWidget *parent) : QWidget(parent) {
    QWidget* mainWidget = new QWidget(this);
    mainWidget->setStyleSheet("background: #272727; border-radius: 20px; width: 200px; height: 500px; ");
    mainWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    QVBoxLayout* mainLayout = new QVBoxLayout;
    mainLayout->addStretch();

    mainWidget->setLayout(mainLayout);
}
