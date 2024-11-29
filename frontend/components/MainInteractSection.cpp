#include "../headers/components/MainInteractSection.h"
#include "../headers/utils/coverFunks.h"
#include <QVBoxLayout>
#include <QScrollArea>
#include <QLayoutItem>
#include <QWidget>

MainInteractSection::MainInteractSection(QWidget *parent) : QWidget(parent) {
    mainWidget = new QWidget();
    mainLayout = new QVBoxLayout(mainWidget);
    mainWidget->setStyleSheet("background: #121212; padding: 5px, 0px; border-radius: 5px;");
    mainWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    QScrollArea* scrollArea = new QScrollArea();
    scrollArea->setWidget(mainWidget);
    scrollArea->setWidgetResizable(true);
    scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scrollArea->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    scrollArea->setStyleSheet(
        " QScrollArea { padding: 0px; border-radius: 5px; border: none; } "
        " QScrollBar:vertical { background: #121212; width: 0px; border: none; } "
        " QScrollBar::handle:vertical { background: #A5A5A5; } "
    );

    this->setLayout(coverWithoutStretchVLayout(scrollArea));
}

void MainInteractSection::loadPage(QWidget *page) {
    QLayoutItem *item;
    while ((item = this->mainLayout->takeAt(0)) != nullptr) {
        delete item->widget();
        delete item;
    }

    this->mainLayout->addWidget(page);
}
