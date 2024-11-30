#include "../headers/components/HoverIconButtonWithStages.h"
#include "../headers/components/HoverIconButton.h"
#include "../headers/utils/globalVariables.h"
#include "../headers/utils/WidgetManager.h"
#include "../headers/utils/UserClasses.h"
#include "../headers/utils/coverFunks.h"
#include "../headers/utils/HttpClient.h"
#include "../headers/pages/MusicPage.h"
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

MusicPage::MusicPage(std::shared_ptr<MusicObject> musicData, QWidget *parent) : QWidget(parent){
    this->musicData = musicData;

    // FIRST INNER SECTION

    profile = new QPushButton();
    profile->setIcon(QIcon(":/assets/picture.png"));
    profile->setFixedSize(160, 160);
    profile->setIconSize(QSize(160, 160));
    QPointer<MusicPage> pointedThis = this;
    if(this->musicData->getProfilePath() != "") {
        HttpClient::sendGetRequest(QUrl(Env::get("SERVER_DOMEN", ":/.env") + "/music/getProfile?path=" + musicData->getProfilePath()),
            [pointedThis](HttpClient::Response* response) {
            if (response->statusCode < 400) {
                if (!pointedThis) return;
                QPixmap pixmap;
                pixmap.loadFromData(response->body);
                pointedThis->profile->setIcon(QIcon(pixmap));
            }
        });
    }

    type = new QLabel("Трек");
    type->setStyleSheet("font-size: 10px; min-width: 0px; color: white; margin: 0px 0px 0px 10px; padding: 0px; font-weight: bold;");
    name = new QLabel(musicData->getName());
    name->setStyleSheet("font-size: 35px; min-width: 0px; width: 700px; color: white; margin: 0px 0px 0px 5px; padding: 0px; font-weight: bold;");
    QString minutes = QString::number(musicData->getDuration() / 60);
    QString seconds = QString::number(musicData->getDuration() % 60);
    metaData = new QLabel(musicData->getAuthor() +
        " • " + musicData->getName() +
        " • " + minutes + ":" + ((seconds.length() == 1) ? "0" + seconds : seconds) +
        " • " + QString::number(musicData->getListens()));
    metaData->setStyleSheet("font-size: 12px; color: #A5A5A5; margin: 0px 0px 0px 10px; padding: 0px; font-weight: bold;");

    QVBoxLayout* topTextLayout = new QVBoxLayout();
    topTextLayout->setAlignment(Qt::AlignBottom);
    topTextLayout->addWidget(type);
    topTextLayout->addWidget(name);
    topTextLayout->addWidget(metaData);

    QHBoxLayout* topLayout = new QHBoxLayout();
    topLayout->addWidget(profile);
    topLayout->addLayout(topTextLayout);


    // SECOND INNER SECTION

    playButton = new QPushButton();
    playButton->setIcon(QIcon(":/assets/player-stop.png"));
    playButton->setIconSize(QSize(25, 25));
    playButton->setStyleSheet("QPushButton { background: green; border-radius: 22px; padding: 12px 8px; margin: 20px 0px 0px; }");
    playButton->connect(playButton, &QPushButton::clicked, [this](){
        HttpClient::sendGetRequest(
            QUrl(Env::get("SERVER_DOMEN", ":/.env") +
                 "/music/recomend?janre=" + this->musicData->getJanres().mid(0, this->musicData->getJanres().size() - 1) +
                 "&author=" + this->musicData->getAuthor() +
                 "&lang=" + this->musicData->getLang() +
                 "&track_name=" + this->musicData->getName() +
                 "&limit=10"),
            [this](HttpClient::Response* response){
            if(response->statusCode < 400) {
                std::vector<std::shared_ptr<MusicObject>> recMusic;
                recMusic.push_back(this->musicData);

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
            User::addMusic(this->musicData);
        } else {
            User::deleteMusic(this->musicData->getId());
        }
        this->loveButton->swapStage();
        Globals::widgetManager->reloadSideBar(WidgetManager::RELOAD_MUSICS);
    });
    for(int i = 0; i < User::getMusicsLength(); i++) {
        if (User::getMusicByInd(i)->getId() == musicData->getId()) {
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

    recsLabel = new QLabel("Рекомендации");
    recsLabel->setStyleSheet("font-size: 13px; color: white; margin: 10px 0px 0px; padding: 0px; font-weight: bold;");
    subRecsLabel = new QLabel("На основе этого трека");
    subRecsLabel->setStyleSheet("font-size: 10px; color: #EDEDED; margin: 0px 0px 0px 3px; padding: 0px;");

    thirdInnerLayout = new QVBoxLayout();
    thirdInnerLayout->addWidget(recsLabel);
    thirdInnerLayout->addWidget(subRecsLabel);
    thirdInnerLayout->setContentsMargins(0, 0, 0, 0);
    thirdInnerLayout->setAlignment(Qt::AlignTop);
    HttpClient::sendGetRequest(
        QUrl(Env::get("SERVER_DOMEN", ":/.env") +
            "/music/recomend?janre=" + musicData->getJanres().mid(0, musicData->getJanres().size() - 1) +
            "&author=" + musicData->getAuthor() +
            "&lang=" + musicData->getLang() +
            "&track_name=" + musicData->getName() +
            "&limit=5"),
        [this](HttpClient::Response* response){
        if(response->statusCode < 400) {
            for(int i = 0; i < response->bodyJsonArray.size(); i++) {
                std::shared_ptr<MusicObject> musicObj = std::make_shared<MusicObject>(response->bodyJsonArray[i].toObject());
                this->thirdInnerLayout->addWidget(new MusicCard(musicObj));
            }
        }
    });


    // MAIN LAYOUT
    QJsonObject authorObject;
    authorObject["id"] = musicData->getAuthorId();
    authorObject["name"] = musicData->getAuthor();
    authorObject["profile"] = musicData->getAuthorProfilePath();

    QWidget* mainWidget = new QWidget();
    mainWidget->setStyleSheet("padding: 20px 0px 0px;");
    QVBoxLayout* mainLayout = new QVBoxLayout();
    mainLayout->addLayout(topLayout);
    mainLayout->addLayout(secondInnerLayout);
    mainLayout->addWidget(new AuthorCard(std::make_shared<AuthorObject>(authorObject)));
    mainLayout->addLayout(thirdInnerLayout);
    mainLayout->setAlignment(Qt::AlignTop);

    this->setLayout(mainLayout);
}

