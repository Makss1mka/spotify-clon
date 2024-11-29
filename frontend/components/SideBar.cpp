#include "../headers/components/AuthorCard.h"
#include "../headers/components/MusicCard.h"
#include "../headers/components/SideBar.h"
#include "../headers/utils/UserClasses.h"
#include "../headers/utils/coverFunks.h"
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QSizePolicy>
#include <QScrollArea>
#include <QLayoutItem>
#include <QPointer>
#include <QLabel>
#include <QSize>

SideBar::SideBar(QWidget *parent) : QWidget(parent) {
    this->currentStage = 1;
    //this->setStyleSheet("background: #121212; border-radius: 5px; width: 300px; max-width: 300px");
    //this->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);

    label = new QLabel("Любимые: ");
    label->setStyleSheet("height: 20px; background: #121212; padding: 0px; margin: 0px 0px 0px 7px; color: #EDEDED;");
    musics = new QPushButton("Треки");
    musics->setStyleSheet("QPushButton { height: 20px; background: #121212; padding: 0px; margin: 0px; color: #EDEDED; }"
            "QPushButton:hover { text-decoration: underline; }");
    musics->connect(musics, &QPushButton::clicked, this, SideBar::musicsClicked);
    authors = new QPushButton("Авторы");
    authors->setStyleSheet("QPushButton { height: 20px; background: #121212; padding: 0px; margin: 0px; color: #EDEDED; }"
            "QPushButton:hover { text-decoration: underline; }");
    authors->connect(authors, &QPushButton::clicked, this, SideBar::authorsClicked);


    QHBoxLayout* navLayout = new QHBoxLayout();
    navLayout->addWidget(label);
    navLayout->addWidget(musics);
    navLayout->addWidget(authors);
    navLayout->addStretch();

    QWidget* scrollBar = new QWidget();
    scrollBarLayout = new QVBoxLayout(scrollBar);
    scrollBarLayout->setContentsMargins(2, 2, 2, 2);
    scrollBarLayout->setAlignment(Qt::AlignTop);
    for(int i = 0; i < User::getMusicsLength(); i++) {
        scrollBarLayout->addWidget(new MusicCard(User::getMusicByInd(i)));
    }

    QScrollArea* scrollArea = new QScrollArea();
    scrollArea->setWidget(scrollBar);
    scrollArea->setWidgetResizable(true);
    scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scrollArea->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
    scrollArea->setStyleSheet(
        " QScrollArea { padding: 0px 0px 15px; height: 100%; border: none; } "
        " QScrollBar:vertical { background: #121212; width: 0px; border: none; color: #121212; } "
        " QScrollBar::handle:vertical { background: #A5A5A5; } "
        " QScrollBar::handle:vertical:hover { background: #EDEDED; } "
        " QScrollBar::sub-line:vertical { background: #121212; }"
        " QScrollBar::add-line:vertical { background: #121212; } "
    );

    QVBoxLayout* mainLayout = new QVBoxLayout;
    mainLayout->addLayout(navLayout);
    mainLayout->addWidget(scrollArea);
    mainLayout->setAlignment(Qt::AlignTop);

    QWidget* mainWidget = new QWidget(this);
    mainWidget->setStyleSheet("background: #121212; padding: 5px, 0px; border-radius: 5px; width: 300px; max-width: 300px;");
    mainWidget->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
    mainWidget->setLayout(mainLayout);

    this->setLayout(coverWithoutStretchVLayout(mainWidget));
}

int SideBar::getCurrentStage() {
    return this->currentStage;
}

void SideBar::musicsClicked() {
    this->currentStage = 1;

    QLayoutItem *item;
    while ((item = this->scrollBarLayout->takeAt(0)) != nullptr) {
        delete item->widget();
        delete item;
    }

    for(int i = 0; i < User::getMusicsLength(); i++) {
        this->scrollBarLayout->addWidget(new MusicCard(User::getMusicByInd(i)));
    }
}

void SideBar::authorsClicked() {
    this->currentStage = 2;

    QLayoutItem *item;
    while ((item = this->scrollBarLayout->takeAt(0)) != nullptr) {
        delete item->widget();
        delete item;
    }

    for(int i = 0; i < User::getAuthorsLength(); i++) {
        this->scrollBarLayout->addWidget(new AuthorCard(User::getAuthorByInd(i)));
    }
}



