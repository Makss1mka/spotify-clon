#include "../headers/components/MusicCard.h"
#include "../headers/utils/HttpClient.h"
#include "../headers/utils/MusicClass.h"
#include "../headers/utils/EnvFile.h"
#include <QSizePolicy>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QWidget>
#include <QPixmap>
#include <QLabel>

MusicCard::MusicCard(std::shared_ptr<MusicObject> musicData, QWidget *parent) : QWidget(parent) {
    this->setStyleSheet("");
    this->setMinimumHeight(80);

    profilePic = new QPushButton(this);
    profilePic->setIcon(QIcon(":/assets/picture.png"));
    profilePic->setFixedSize(38, 38);
    profilePic->setIconSize(QSize(38, 38));
    profilePic->setStyleSheet("background: inherit; ");
    profilePic->connect(profilePic, &QPushButton::clicked, this, &MusicCard::trackProfileClicked);
    HttpClient::sendGetRequest(QUrl(Env::get("SERVER_DOMEN", ":/.env") + "/music/getProfile?path=" + musicData->getProfilePath()),
        [this](HttpClient::Response* response) {
            if (response->statusCode < 400) {
                QPixmap pixmap;
                pixmap.loadFromData(response->body);
                this->profilePic->setIcon(QIcon(pixmap));
            }
    });

    nameLabel = new QPushButton(musicData->getName(), this);
    nameLabel->setStyleSheet("QPushButton { max-height: 13px; font-size: 13px; text-align: left; border: 1px solid yellow; background: inherit; color: white; margin: 0px 0px 2px; padding: 0px; }"
            "QPushButton:hover { text-decoration: underline; }");
    nameLabel->adjustSize();
    nameLabel->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
    connect(nameLabel, &QPushButton::clicked, this, &MusicCard::trackNameClicked);

    authorLabel = new QPushButton(musicData->getAuthor(), this);
    authorLabel->setStyleSheet("QPushButton { max-height: 11px; text-align: left; border: 1px solid yellow; background: inherit; font-size: 11px; color: #CDCDCD; padding: 0px; }"
            "QPushButton:hover { text-decoration: underline; }");
    authorLabel->adjustSize();
    authorLabel->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
    connect(authorLabel, &QPushButton::clicked, this, &MusicCard::trackAuthorClicked);


    QVBoxLayout *textLayout = new QVBoxLayout();
    textLayout->setSpacing(0);
    textLayout->setContentsMargins(2, 2, 2, 2);
    textLayout->addWidget(nameLabel);
    textLayout->addWidget(authorLabel);

    QHBoxLayout *mainLayout = new QHBoxLayout(this);
    mainLayout->addWidget(profilePic);
    mainLayout->addLayout(textLayout);
    mainLayout->addStretch();
    setLayout(mainLayout);
}

void MusicCard::trackNameClicked() {

}

void MusicCard::trackAuthorClicked() {

}

void MusicCard::trackProfileClicked() {

}

