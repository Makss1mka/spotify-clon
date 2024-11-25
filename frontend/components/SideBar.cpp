#include "../headers/components/MusicCard.h"
#include "../headers/components/SideBar.h"
#include "../headers/utils/UserClasses.h"
#include "../headers/utils/coverFunks.h"
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QSizePolicy>
#include <QScrollArea>
#include <QLabel>
#include <QListWidget>

SideBar::SideBar(QWidget *parent) : QWidget(parent) {
    this->setStyleSheet("background: #272727; border-radius: 20px; height: 100%; width: 300px; max-width: 300px");
    this->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    label = new QLabel("Любимые: ");
    label->setStyleSheet("background: inherit; padding: 0px; margin: 0px; color: #EDEDED;");
    musics = new QPushButton("Треки");
    musics->setStyleSheet("QPushButton { background: inherit; padding: 0px; margin: 0px; color: #EDEDED; }"
            "QPushButton:hover { text-decoration: underline; }");
    authors = new QPushButton("Авторы");
    authors->setStyleSheet("QPushButton { background: inherit; padding: 0px; margin: 0px; color: #EDEDED; }"
            "QPushButton:hover { text-decoration: underline; }");

    QHBoxLayout* navLayout = new QHBoxLayout();
    navLayout->addWidget(label);
    navLayout->addWidget(musics);
    navLayout->addWidget(authors);
    navLayout->addStretch();

    //QWidget* scrollBar = new QWidget();
    //QVBoxLayout* scrollBarLayout = new QVBoxLayout();
    QListWidget* list = new QListWidget();
    for(int i = 0; i < User::getMusicsLength(); i++) {
        QListWidgetItem* listItem = new QListWidgetItem(list);

        list->setItemWidget(listItem, new MusicCard(User::getMusicByInd(i)));
    }

    // QScrollArea* scrollArea = new QScrollArea();
    // scrollArea->setWidget(scrollBar);
    // scrollArea->setWidgetResizable(true);
    // scrollArea->setStyleSheet("border: none;");

    QVBoxLayout* mainLayout = new QVBoxLayout;
    mainLayout->addLayout(navLayout);
    mainLayout->addWidget(list);
    this->setLayout(mainLayout);
}
