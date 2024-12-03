#include "../headers/components/MainInteractSection.h"
#include "../headers/utils/globalVariables.h"
#include "../headers/components/MusicCard.h"
#include "../headers/utils/coverFunks.h"
#include "../headers/utils/HttpClient.h"
#include "../headers/utils/MusicClass.h"
#include "../headers/pages/AuthorPage.h"
#include "../headers/pages/MusicPage.h"
#include "../headers/utils/EnvFile.h"
#include <QSizePolicy>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QEnterEvent>
#include <QJsonObject>
#include <QPointer>
#include <QWidget>
#include <QPixmap>
#include <QLabel>
#include <QEvent>

MusicCard::MusicCard(std::shared_ptr<MusicObject> musicData, QWidget *parent) : QWidget(parent) {
    this->musicData = musicData;
    this->setStyleSheet("margin: 0px; padding: 0px; max-height: 80px; max-width: 290px");
    setMouseTracking(true);

    mainWidget = new QWidget(this);
    //mainWidget->setStyleSheet("height: 50px; max-width: 290px;");
    mainWidget->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    profilePic = new QPushButton(mainWidget);
    profilePic->setIcon(QIcon(":/assets/picture.png"));
    profilePic->setFixedSize(45, 45);
    profilePic->setIconSize(QSize(45, 45));
    profilePic->connect(profilePic, &QPushButton::clicked, this, &MusicCard::trackProfileClicked);
    QPointer<MusicCard> pointedThis = this;
    if(musicData->getProfilePath() != "") {
        HttpClient::sendGetRequest(QUrl(Env::get("SERVER_DOMEN") + "/music/getProfile?path=" + musicData->getProfilePath()),
            [pointedThis](HttpClient::Response* response) {
            if (response->statusCode < 400) {
                if (!pointedThis) return;
                QPixmap pixmap;
                pixmap.loadFromData(response->body);
                pointedThis->profilePic->setIcon(QIcon(pixmap));
            }
        });
    }

    nameLabel = new QPushButton(musicData->getName(), mainWidget);
    nameLabel->setStyleSheet("QPushButton { height: 13px; font-size: 13px; text-align: left; background: #121212; color: white; margin: 0px 0px 2px; padding: 0px; }"
            "QPushButton:hover { text-decoration: underline; }");
    nameLabel->adjustSize();
    nameLabel->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
    connect(nameLabel, &QPushButton::clicked, this, &MusicCard::trackNameClicked);

    authorLabel = new QPushButton(musicData->getAuthor(), mainWidget);
    authorLabel->setStyleSheet("QPushButton { height: 11px; font-size: 11px; text-align: left; background: #121212; color: #CDCDCD; padding: 0px; }"
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

    mainWidget->setStyleSheet("height: 60px; margin: 0px; padding: 0px; background: #121212; padding: 5px, 0px; border-radius: 10px;");
    mainWidget->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
    mainWidget->setLayout(mainLayout);

    this->setLayout(coverWithoutStretchHLayout(mainWidget));
}

void MusicCard::trackNameClicked() {
    Globals::widgetManager->loadPage(new MusicPage(musicData));
}

void MusicCard::trackAuthorClicked() {
    QJsonObject authorObject;
    authorObject["id"] = musicData->getAuthorId();
    authorObject["name"] = musicData->getAuthor();
    authorObject["profile"] = musicData->getAuthorProfilePath();

    Globals::widgetManager->loadPage(new AuthorPage(std::make_shared<AuthorObject>(authorObject)));
}

void MusicCard::trackProfileClicked() {

}

void MusicCard::enterEvent(QEnterEvent *event) {
    setCursor(Qt::PointingHandCursor);
    this->mainWidget->setStyleSheet("height: 60px; margin: 0px; padding: 0px; background: #2a2a2a; padding: 5px, 0px; border-radius: 10px;");
    this->authorLabel->setStyleSheet("QPushButton { height: 11px; font-size: 11px; text-align: left; background: #2a2a2a; color: #CDCDCD; padding: 0px; }"
            "QPushButton:hover { text-decoration: underline; }");
    this->nameLabel->setStyleSheet("QPushButton { height: 13px; font-size: 13px; text-align: left; background: #2a2a2a; color: white; margin: 0px 0px 2px; padding: 0px; }"
            "QPushButton:hover { text-decoration: underline; }");
    QWidget::enterEvent(event);
}

void MusicCard::leaveEvent(QEvent *event) {
    unsetCursor();
    this->mainWidget->setStyleSheet("height: 60px; margin: 0px; padding: 0px; background: #121212; padding: 5px, 0px; border-radius: 10px;");
    this->authorLabel->setStyleSheet("QPushButton { height: 11px; font-size: 11px; text-align: left; background: #121212; color: #CDCDCD; padding: 0px; }"
            "QPushButton:hover { text-decoration: underline; }");
    this->nameLabel->setStyleSheet("QPushButton { height: 13px; font-size: 13px; text-align: left; background: #121212; color: white; margin: 0px 0px 2px; padding: 0px; }"
            "QPushButton:hover { text-decoration: underline; }");
    QWidget::leaveEvent(event);
}


