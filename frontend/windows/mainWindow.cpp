#include "../headers/windows/MainWindow.h"
#include "../headers/utils/coverFunks.h"
#include "../headers/components/Header.h"
#include "../headers/components/Player.h"
#include "../headers/components/SideBar.h"
#include "../headers/components/MainInteractSection.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QSpacerItem>
#include <QFont>
#include <QWidget>
#include <QSizePolicy>

MainWindow::MainWindow(QWidget *parent) : QWidget(parent) {
    QVBoxLayout* mainLayout = new QVBoxLayout(this);

    mainLayout->addWidget(new Header());

    QHBoxLayout* mainSectionLayout = new QHBoxLayout();
    mainSectionLayout->addWidget(new SideBar(), 1);
    mainSectionLayout->addWidget(new MainInteractSection(), 5);
    mainSectionLayout->setSpacing(6);
    mainLayout->addLayout(mainSectionLayout);

    mainLayout->addWidget(new Player());

    this->setLayout(mainLayout);
}
