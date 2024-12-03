#include "../headers/components/MainInteractSection.h"
#include "../headers/utils/globalVariables.h"
#include "../headers/windows/MainWindow.h"
#include "../headers/components/SideBar.h"
#include "../headers/components/Header.h"
#include "../headers/components/Footer.h"
#include "../headers/utils/coverFunks.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QWidget>

MainWindow::MainWindow(QWidget *parent) : QWidget(parent) {
    this->setMinimumSize(600, 500);

    QVBoxLayout* mainLayout = new QVBoxLayout(this);

    mainLayout->addWidget(new Header(this));

    SideBar* sideBar = new SideBar();
    MainInteractSection* main = new MainInteractSection();

    Globals::widgetManager->connectPageDist(main);
    Globals::widgetManager->connectSideBar(sideBar);

    QHBoxLayout* mainSectionLayout = new QHBoxLayout();
    mainSectionLayout->addWidget(sideBar);
    mainSectionLayout->addWidget(main);
    mainSectionLayout->setSpacing(0);

    QWidget* centralBlock = new QWidget(this);
    centralBlock->setLayout(mainSectionLayout);
    mainLayout->addWidget(centralBlock);

    mainLayout->addWidget(new Footer(this));

    this->setLayout(mainLayout);
}
