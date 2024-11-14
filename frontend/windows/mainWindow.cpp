#include "../headers/windows/MainWindow.h"
#include "../headers/utils/coverFunks.h"
#include "../headers/components/Header.h"
#include "../headers/components/Footer.h"
#include "../headers/components/SideBar.h"
#include "../headers/components/MainInteractSection.h"
#include "../headers/utils/globalVariables.h"
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

    mainLayout->addWidget(new Header(this));

    QHBoxLayout* mainSectionLayout = new QHBoxLayout();
    mainSectionLayout->addWidget(new SideBar());
    mainSectionLayout->addWidget(new MainInteractSection());
    mainSectionLayout->setSpacing(6);
    mainLayout->addLayout(mainSectionLayout);

    mainLayout->addWidget(new Footer(this));

    this->setLayout(mainLayout);
}
