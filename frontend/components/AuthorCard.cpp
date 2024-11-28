#include "../headers/components/AuthorCard.h"
#include "../headers/utils/coverFunks.h"
#include "../headers/utils/HttpClient.h"
#include "../headers/utils/MusicClass.h"
#include "../headers/utils/EnvFile.h"
#include <QSizePolicy>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QEnterEvent>
#include <QPointer>
#include <QWidget>
#include <QPixmap>
#include <QLabel>
#include <QEvent>
#include <QSize>
#include <QIcon>

AuthorCard::AuthorCard(std::shared_ptr<AuthorObject> authorData, QWidget *parent) : QWidget(parent) {
    this->setStyleSheet("margin: 0px; padding: 0px; max-height: 80px; max-width: 290px");
    setMouseTracking(true);

    mainWidget = new QWidget(this);

    profilePic = new QPushButton(mainWidget);
    profilePic->setIcon(QIcon(":/assets/picture.png"));
    profilePic->setFixedSize(45, 45);
    profilePic->setIconSize(QSize(45, 45));
    profilePic->connect(profilePic, &QPushButton::clicked, this, &AuthorCard::trackProfileClicked);
    QPointer<AuthorCard> pointedThis = this;
    HttpClient::sendGetRequest(QUrl(Env::get("SERVER_DOMEN", ":/.env") + "/music/getProfile?path=" + authorData->getProfilePath()),
        [pointedThis](HttpClient::Response* response) {
            if (response->statusCode < 400) {
                QPixmap pixmap;
                pixmap.loadFromData(response->body);
                pixmap = pixmap.scaled(45, 45, Qt::KeepAspectRatio, Qt::SmoothTransformation);
                pointedThis->profilePic->setIcon(QIcon(pixmap));
                pointedThis->profilePic->setIconSize(QSize(45, 45));
            }
        });


    label = new QLabel("Исполнитель:");
    label->setStyleSheet("QLabel { height: 11px; font-size: 11px; text-align: left; background: #121212; color: #CDCDCD; margin: 0px 0px 2px; padding: 0px; }"
            "QLabel:hover { text-decoration: underline; }");

    nameLabel = new QPushButton(authorData->getName(), mainWidget);
    nameLabel->setStyleSheet("QPushButton { height: 13px; font-size: 13px; text-align: left; background: #121212; color: white; padding: 0px; }"
            "QPushButton:hover { text-decoration: underline; }");
    nameLabel->connect(nameLabel, &QPushButton::clicked, this, &AuthorCard::trackNameClicked);


    QVBoxLayout *textLayout = new QVBoxLayout();
    textLayout->setSpacing(0);
    textLayout->setContentsMargins(2, 2, 2, 2);
    textLayout->addWidget(label);
    textLayout->addWidget(nameLabel);

    QHBoxLayout *mainLayout = new QHBoxLayout(this);
    mainLayout->addWidget(profilePic);
    mainLayout->addLayout(textLayout);
    mainLayout->addStretch();

    mainWidget->setStyleSheet("height: 60px; margin: 0px; padding: 0px; background: #121212; padding: 5px, 0px; border-radius: 10px;");
    mainWidget->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
    mainWidget->setLayout(mainLayout);

    this->setLayout(coverWithoutStretchHLayout(mainWidget));
}

void AuthorCard::trackNameClicked() {

}

void AuthorCard::trackAuthorClicked() {

}

void AuthorCard::trackProfileClicked() {

}

void AuthorCard::enterEvent(QEnterEvent *event) {
    setCursor(Qt::PointingHandCursor);
    this->mainWidget->setStyleSheet("height: 60px; margin: 0px; padding: 0px; background: #2a2a2a; padding: 5px, 0px; border-radius: 10px;");
    this->label->setStyleSheet("QLabel { height: 11px; font-size: 11px; text-align: left; background: #2a2a2a; color: #CDCDCD; margin: 0px 0px 2px; padding: 0px; }"
            "QLabel:hover { text-decoration: underline; }");
    this->nameLabel->setStyleSheet("QPushButton { height: 13px; font-size: 13px; text-align: left; background: #2a2a2a; color: white;padding: 0px; }"
            "QPushButton:hover { text-decoration: underline; }");
    QWidget::enterEvent(event);
}

void AuthorCard::leaveEvent(QEvent *event) {
    unsetCursor();
    this->mainWidget->setStyleSheet("height: 60px; margin: 0px; padding: 0px; background: #121212; padding: 5px, 0px; border-radius: 10px;");
    this->label->setStyleSheet("QLabel { height: 11px; font-size: 11px; text-align: left; background: #121212; color: #CDCDCD; margin: 0px 0px 2px; padding: 0px; }"
            "QLabel:hover { text-decoration: underline; }");
    this->nameLabel->setStyleSheet("QPushButton { height: 13px; font-size: 13px; text-align: left; background: #121212; color: white; padding: 0px; }"
            "QPushButton:hover { text-decoration: underline; }");
    QWidget::leaveEvent(event);
}
