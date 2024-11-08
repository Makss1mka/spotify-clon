#include "../headers/components/Header.h"
#include "../headers/utils/coverFunks.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QWidget>
#include <QIcon>
#include <QSizePolicy>
#include <QSize>

Header::Header(QWidget *parent) : QWidget(parent) {
    this->setFixedHeight(60);
    //this->setStyleSheet("background-color: black");

    // first section
    QPushButton *leftAngleButton = new QPushButton;
    leftAngleButton->setFixedSize(20, 20);
    leftAngleButton->setIcon(QIcon(":/assets/angle-left.png"));
    leftAngleButton->setStyleSheet("backround-color: inherit");
    QPushButton *rightAngleButton = new QPushButton;
    rightAngleButton->setFixedSize(20, 20);
    rightAngleButton->setIcon(QIcon(":/assets/angle-right.png"));
    rightAngleButton->setStyleSheet("backround-color: inherit");

    QHBoxLayout *leftLayout = new QHBoxLayout;
    leftLayout->addWidget(leftAngleButton);
    leftLayout->addWidget(rightAngleButton);

    // second section
    QPushButton *homeButton = new QPushButton;
    homeButton->setIcon(QIcon(":/assets/home.png"));
    homeButton->setFixedSize(40, 40);
    homeButton->setStyleSheet("background-color: #272727; border-radius: 20px;");

    QLineEdit *searchInputField = new QLineEdit;
    searchInputField->setPlaceholderText("Что хотите послушать");
    searchInputField->setStyleSheet("background-color: #272727; border-radius: 10px; color: white;");
    QPushButton *searchButton = new QPushButton;
    searchButton->setIcon(QIcon(":/assets/search.png"));
    searchButton->setFixedSize(30, 30);
    QHBoxLayout *searchLayout = new QHBoxLayout;
    searchLayout->addLayout(coverWithVLayout(searchButton));
    searchLayout->addLayout(coverWithVLayout(searchInputField));
    QWidget *searchBar = new QWidget;
    searchBar->setStyleSheet("background-color: #272727; border-radius: 15px;");
    searchBar->setLayout(searchLayout);

    QHBoxLayout *centerLayout = new QHBoxLayout;
    centerLayout->addWidget(homeButton);
    centerLayout->addWidget(searchBar);

    // third section
    QPushButton *userButton = new QPushButton;
    userButton->setIcon(QIcon(":/assets/user.png"));
    userButton->setFixedSize(40, 40);
    userButton->setStyleSheet("background-color: #272727; border-radius: 20px;");

    QPushButton *collapseButton = new QPushButton;
    collapseButton->setIcon(QIcon(":/assets/line.png"));
    collapseButton->setStyleSheet("backround-color: inherit");
    homeButton->setStyleSheet("background-color: #272727; border-radius: 20px;");
    QPushButton *collapseInWindowButton = new QPushButton;
    collapseInWindowButton->setIcon(QIcon(":/assets/square.png"));
    collapseInWindowButton->setStyleSheet("backround-color: inherit");
    QPushButton *exitButton = new QPushButton;
    exitButton->setIcon(QIcon(":/assets/cross.png"));
    exitButton->setStyleSheet("backround-color: inherit");

    QHBoxLayout *rightLayout = new QHBoxLayout;
    rightLayout->addWidget(userButton);
    rightLayout->addWidget(collapseButton);
    rightLayout->addWidget(collapseInWindowButton);
    rightLayout->addWidget(exitButton);

    // main layout
    QHBoxLayout* mainLayout = new QHBoxLayout;
    mainLayout->addLayout(leftLayout);
    mainLayout->addStretch();
    mainLayout->addLayout(centerLayout);
    mainLayout->addStretch();
    mainLayout->addLayout(rightLayout);

    this->setLayout(mainLayout);
}
