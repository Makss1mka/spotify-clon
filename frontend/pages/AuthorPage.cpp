#include "../headers/components/HoverIconButtonWithStages.h"
#include "../headers/components/HoverIconButton.h"
#include "../headers/utils/globalVariables.h"
#include "../headers/components/MusicCard.h"
#include "../headers/utils/WidgetManager.h"
#include "../headers/utils/UserClasses.h"
#include "../headers/utils/MusicClass.h"
#include "../headers/utils/coverFunks.h"
#include "../headers/utils/HttpClient.h"
#include "../headers/pages/AuthorPage.h"
#include "../headers/utils/EnvFile.h"
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QScrollArea>
#include <QJsonObject>
#include <QPointer>
#include <QWidget>
#include <QPixmap>
#include <QLabel>
#include <QIcon>
#include <QFile>
#include <QSizePolicy>

AuthorPage::AuthorPage(std::shared_ptr<AuthorObject> authorData, QWidget *parent) : QWidget(parent){
    this->authorData = authorData;

    // FIRST INNER SECTION

    profileBac = new QPushButton();
    profileBac->setIcon(QIcon(":/assets/picture.png"));
    profileBac->setFixedSize(160, 160);
    profileBac->setIconSize(QSize(160, 160));
    QPointer<AuthorPage> pointedThis = this;
    if(this->authorData->getProfilePath() != "") {
        HttpClient::sendGetRequest(QUrl(Env::get("SERVER_DOMEN", ":/.env") + "/music/getProfile?path=" + authorData->getProfilePath()),
            [pointedThis](HttpClient::Response* response) {
            if (response->statusCode < 400) {
                if (!pointedThis) return;
                QPixmap pixmap;
                pixmap.loadFromData(response->body);
                pointedThis->profileBac->setIcon(QIcon(pixmap));
            }
        });
    }

    type = new QLabel("Исполнитель");
    type->setStyleSheet("font-size: 10px; min-width: 0px; color: white; margin: 0px 0px 0px 20px; padding: 0px; font-weight: bold;");
    name = new QLabel(authorData->getName());
    name->setStyleSheet("font-size: 35px; min-width: 0px; width: 700px; color: white; margin: 0px 0px 0px 12px; padding: 0px; font-weight: bold;");
    metaData = new QLabel("Тут чето будет");
    metaData->setStyleSheet("font-size: 12px; color: #A5A5A5; margin: 0px 0px 0px 20px; padding: 0px; font-weight: bold;");

    QVBoxLayout* topTextLayout = new QVBoxLayout();
    topTextLayout->setAlignment(Qt::AlignBottom);
    topTextLayout->addWidget(type);
    topTextLayout->addWidget(name);
    topTextLayout->addWidget(metaData);

    QHBoxLayout* topLayout = new QHBoxLayout();
    topLayout->addWidget(profileBac);
    topLayout->addLayout(topTextLayout);

    // SECOND INNER SECTION

    playButton = new QPushButton();
    playButton->setIcon(QIcon(":/assets/player-stop.png"));
    playButton->setIconSize(QSize(25, 25));
    playButton->setStyleSheet("QPushButton { background: green; border-radius: 22px; padding: 12px 8px; margin: 20px 0px 0px; }");
    playButton->connect(playButton, &QPushButton::clicked, [this](){
        HttpClient::sendGetRequest(
            QUrl(Env::get("SERVER_DOMEN", ":/.env") + "/music/getByAuthor?author_name=" + this->authorData->getName()),
            [this](HttpClient::Response* response){
            if(response->statusCode < 400) {
                std::vector<std::shared_ptr<MusicObject>> recMusic;

                QJsonArray loadedMusic = response->bodyJsonArray;
                for(int i = 0; i < loadedMusic.size(); i++) {
                    recMusic.push_back(std::make_shared<MusicObject>(loadedMusic[i].toObject()));
                }

                Globals::player->setPlaylist(recMusic);
            }
        });
    });

    loveButton = new HoverIconButtonWithStages(
        QIcon(":/assets/heart.png"),
        QIcon(":/assets/heart-active.png"),
        QIcon(":/assets/heart-pressed.png"),
        QIcon(":/assets/heart-pressed.png")
    );
    loveButton->setIconSize(QSize(25, 25));
    loveButton->setStyleSheet("padding: 12px 8px; margin: 20px 0px 0px; ");
    loveButton->connect(loveButton, &QPushButton::clicked, [this](){
        if(this->loveButton->isButtonClicked() == false) {
            User::addAuthor(this->authorData);
        } else {
            User::deleteAuthor(this->authorData->getId());
        }
        this->loveButton->swapStage();
        Globals::widgetManager->reloadSideBar(WidgetManager::RELOAD_AUTHORS);
    });
    for(int i = 0; i < User::getAuthorsLength(); i++) {
        if (User::getAuthorByInd(i)->getId() == this->authorData->getId()) {
            loveButton->swapStage();
        }
    }

    optionsButton = new HoverIconButton(QIcon(":/assets/dots.png"), QIcon(":/assets/dots-active.png"));
    optionsButton->setIconSize(QSize(25, 25));
    optionsButton->setFixedSize(25, 25);
    optionsButton->setStyleSheet("padding: 12px 8px; margin: 20px 0px 0px; ");

    QHBoxLayout* secondInnerLayout = new QHBoxLayout();
    secondInnerLayout->addWidget(playButton);
    secondInnerLayout->addWidget(loveButton);
    secondInnerLayout->addWidget(optionsButton);
    secondInnerLayout->setAlignment(Qt::AlignLeft);


    // THIRD INNER SECTION

    popularTracks = new QLabel("Популярные треки исполнителя");
    popularTracks->setStyleSheet("max-height: 16px; font-size: 13px; color: white; margin: 10px 0px 0px; padding: 0px; font-weight: bold;");

    thirdInnerLayout = new QVBoxLayout();
    thirdInnerLayout->addWidget(popularTracks);
    thirdInnerLayout->setContentsMargins(0, 0, 0, 0);
    thirdInnerLayout->setAlignment(Qt::AlignTop);
    HttpClient::sendGetRequest(
        QUrl(Env::get("SERVER_DOMEN", ":/.env") + "/music/getByAuthor?author_name=" + this->authorData->getName()),
        [this](HttpClient::Response* response){
            if(response->statusCode < 400) {
                for(int i = 0; i < response->bodyJsonArray.size(); i++) {
                    std::shared_ptr<MusicObject> musicObj = std::make_shared<MusicObject>(response->bodyJsonArray[i].toObject());
                    this->thirdInnerLayout->addWidget(new MusicCard(musicObj));
                }
            }
        });


    // MAIN LAYOUT

    QWidget* mainWidget = new QWidget();
    mainWidget->setStyleSheet("padding: 20px 0px 0px;");
    QVBoxLayout* mainLayout = new QVBoxLayout();
    mainLayout->addLayout(topLayout);
    mainLayout->addLayout(secondInnerLayout);
    mainLayout->addLayout(thirdInnerLayout);
    mainLayout->setAlignment(Qt::AlignTop);

    this->setLayout(mainLayout);
}


