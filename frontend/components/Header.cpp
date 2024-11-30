#include "../headers/components/HoverIconButton.h"
#include "../headers/utils/globalVariables.h"
#include "../headers/components/Header.h"
#include "../headers/utils/coverFunks.h"
#include "../headers/pages/SearchPage.h"
#include "../headers/app.h"
#include <QRegularExpressionValidator>
#include <QRegularExpression>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QSizePolicy>
#include <QLineEdit>
#include <QWidget>
#include <QIcon>
#include <QSize>

Header::Header(QWidget *parent) : QWidget(parent) {
    this->setFixedHeight(60);

    // --- First inner section

    // Back button
    backButton = new HoverIconButton(QIcon(":/assets/angle-left.png"), QIcon(":/assets/angle-left-active.png"));
    backButton->setFixedSize(20, 20);
    backButton->setStyleSheet("background: inherit");

    // Next button
    nextButton = new HoverIconButton(QIcon(":/assets/angle-right.png"), QIcon(":/assets/angle-right-active.png"));
    nextButton->setFixedSize(20, 20);
    nextButton->setStyleSheet("background: inherit");

    // Firxt inner layout
    QHBoxLayout *leftLayout = new QHBoxLayout;
    leftLayout->addWidget(backButton);
    leftLayout->addWidget(nextButton);

    // --- Second inner section

    // Home button
    homeButton = new HoverIconButton(QIcon(":/assets/home.png"), QIcon(":/assets/home-active.png"));
    homeButton->setFixedSize(40, 40);
    homeButton->setStyleSheet("background: #272727; border-radius: 20px;");

    // Search input field
    searchInputField = new QLineEdit;
    searchInputField->setPlaceholderText("Что хотите послушать");
    searchInputField->setStyleSheet("background: #272727; border-radius: 10px; color: white;");
    QRegularExpression regExp("[A-Za-z0-9]*");
    QRegularExpressionValidator validator(regExp, searchInputField);
    searchInputField->setValidator(&validator);

    // Search button
    searchButton = new HoverIconButton(QIcon(":/assets/search.png"), QIcon(":/assets/search-active.png"));
    searchButton->setFixedSize(30, 30);
    searchButton->connect(searchButton, &QPushButton::clicked, [this](){
        Globals::widgetManager->loadPage(new SearchPage(this->searchInputField->text()));
    });

    // Search layout
    QHBoxLayout *searchLayout = new QHBoxLayout;
    searchLayout->addLayout(coverWithVLayout(searchButton));
    searchLayout->addLayout(coverWithVLayout(searchInputField));

    // Search bar widget
    QWidget *searchBar = new QWidget;
    searchBar->setStyleSheet("background: #272727; border-radius: 15px;");
    searchBar->setLayout(searchLayout);

    // Second inner layout
    QHBoxLayout *centerLayout = new QHBoxLayout;
    centerLayout->addWidget(homeButton);
    centerLayout->addWidget(searchBar);

    // --- Third inner section

    // User button
    userButton = new HoverIconButton(QIcon(":/assets/user.png"), QIcon(":/assets/user-active.png"));
    userButton->setFixedSize(40, 40);
    userButton->setStyleSheet("background: #272727; border-radius: 20px;");

    // Collapse button
    collapseButton = new HoverIconButton(QIcon(":/assets/line.png"), QIcon(":/assets/line-active.png"));
    collapseButton->setStyleSheet("background: inherit");
    collapseButton->connect(collapseButton, &QPushButton::clicked, &App::showNormal);

    // Collapse in window button
    collapseInWindowButton = new HoverIconButton(QIcon(":/assets/square.png"), QIcon(":/assets/square-active.png"));
    collapseInWindowButton->setStyleSheet("background: inherit");
    collapseInWindowButton->connect(collapseInWindowButton, &QPushButton::clicked, &App::showMinimized);

    // Exit button
    exitButton = new HoverIconButton(QIcon(":/assets/cross.png"), QIcon(":/assets/cross-active.png"));
    exitButton->setStyleSheet("background: inherit");
    exitButton->connect(exitButton, &QPushButton::clicked, &App::close);

    // Third inner layout
    QHBoxLayout *rightLayout = new QHBoxLayout;
    rightLayout->addWidget(userButton);
    rightLayout->addWidget(collapseButton);
    rightLayout->addWidget(collapseInWindowButton);
    rightLayout->addWidget(exitButton);

    // --- Main layout
    QHBoxLayout* mainLayout = new QHBoxLayout;
    mainLayout->addLayout(leftLayout);
    mainLayout->addStretch();
    mainLayout->addLayout(centerLayout);
    mainLayout->addStretch();
    mainLayout->addLayout(rightLayout);

    this->setLayout(mainLayout);
}
