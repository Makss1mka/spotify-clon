#include "../headers/components/HoverIconButtonWithStages.h"
#include "../headers/components/HoverIconButton.h"
#include "../headers/components/VolumeSlider.h"
#include "../headers/components/SoundButton.h"
#include "../headers/components/MusicSlider.h"
#include "../headers/components/Footer.h"
#include "../headers/pages/AuthorPage.h"
#include "../headers/pages/MusicPage.h"
#include "../headers/utils/globalVariables.h"
#include "../headers/utils/UserClasses.h"
#include "../headers/utils/MusicClass.h"
#include "../headers/utils/HttpClient.h"
#include "../headers/utils/EnvFile.h"
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QSlider>
#include <QWidget>
#include <QPixmap>
#include <QLabel>
#include <QTimer>
#include <QIcon>
#include <QSize>
#include <QFile>
#include <QList>

Footer::Footer(QWidget *parent) : QWidget(parent) {
    this->setFixedHeight(70);

    // --- First inner section

    // Music image
    musicImage = new QPushButton;
    musicImage->setIcon(QIcon(":/assets/picture.png"));
    musicImage->setFixedSize(50, 50);
    musicImage->setIconSize(QSize(50, 50));
    musicImage->connect(musicImage, &QPushButton::clicked, [this](){
        Globals::widgetManager->loadPage(new MusicPage(Globals::player->getCurrentMusic()));
    });

    // Music data labels
    nameLabel = new QPushButton("Test name");
    nameLabel->setStyleSheet("QPushButton { text-align: left; width: 200px; color: white; margin: 0px; padding: 0px; } "
            "QPushButton:hover { text-decoration: underline; }");
    nameLabel->connect(nameLabel, &QPushButton::clicked, [this](){
        Globals::widgetManager->loadPage(new MusicPage(Globals::player->getCurrentMusic()));
    });
    authorLabel = new QPushButton("Test author");
    authorLabel->setStyleSheet("QPushButton { text-align: left; width: 200px; font-size: 11px; color: #CDCDCD; padding: 0px; } "
            "QPushButton:hover { text-decoration: underline; }");
    authorLabel->connect(authorLabel, &QPushButton::clicked, [this](){
        QJsonObject authorObject;
        authorObject["id"] = Globals::player->getCurrentMusic()->getAuthorId();
        authorObject["name"] = Globals::player->getCurrentMusic()->getAuthor();
        authorObject["profile"] = Globals::player->getCurrentMusic()->getAuthorProfilePath();

        Globals::widgetManager->loadPage(new AuthorPage(std::make_shared<AuthorObject>(authorObject)));
    });


    // Labels layout
    QVBoxLayout *textLayout = new QVBoxLayout;
    textLayout->setSpacing(0);
    textLayout->setContentsMargins(6, 8, 6, 8);
    textLayout->addWidget(nameLabel);
    textLayout->addWidget(authorLabel);


    // First inner layout
    QHBoxLayout *firstInnerLayout = new QHBoxLayout;
    firstInnerLayout->addWidget(musicImage);
    firstInnerLayout->addLayout(textLayout);


    // --- Second inner section

    // Shuffle Button
    shuffleButton = new HoverIconButtonWithStages(QIcon(":/assets/shuffle.png"), QIcon(":/assets/shuffle-active.png"),
            QIcon(":/assets/no-shuffle.png"), QIcon(":/assets/no-shuffle-active.png"));
    shuffleButton->setStyleSheet("background: inherit");
    shuffleButton->connect(shuffleButton, QPushButton::clicked, [this](){
        this->shuffleButton->swapStage();
    });


    // Back button
    backButton = new HoverIconButton(QIcon(":/assets/back.png"), QIcon(":/assets/back-active.png"));
    backButton->setStyleSheet("background: inherit");
    backButton->connect(backButton, QPushButton::clicked, [this](){
        if (Globals::player->prev() == false) return;
        this->musicTimeline->setValue(0);
    });


    // Next Button
    nextButton = new HoverIconButton(QIcon(":/assets/next.png"), QIcon(":/assets/next-active.png"));
    nextButton->setStyleSheet("background: inherit");
    nextButton->connect(nextButton, QPushButton::clicked, [this](){
        if (Globals::player->next() == false) return;
        this->musicTimeline->setValue(0);
    });


    // Repeat button
    repeatButton = new HoverIconButtonWithStages(QIcon(":/assets/repeat.png"), QIcon(":/assets/repeat-active.png"),
            QIcon(":/assets/repeat-once.png"), QIcon(":/assets/repeat-once-active.png"));
    repeatButton->setStyleSheet("background: inherit");
    repeatButton->connect(repeatButton, QPushButton::clicked, [this](){
        Globals::player->swapRepeating();
        this->repeatButton->swapStage();
    });


    // Stop button
    stopButton = new QPushButton;
    stopButton->setIcon(QIcon(":/assets/player-stop.png"));
    stopButton->setIconSize(QSize(20, 20));
    stopButton->setFixedSize(30, 30);
    stopButton->setStyleSheet("QPushButton { background: white; border-radius: 15px; }");
    stopButton->connect(stopButton, QPushButton::clicked, [this](){
        if (Globals::player->isCurrentTrackLoaded() == false) return;
        if (Globals::player->isPlayerPaused() == true) {
            Globals::player->play();
            this->stopButton->setIcon(QIcon(":/assets/player-go.png"));
        } else {
            Globals::player->pause();
            this->stopButton->setIcon(QIcon(":/assets/player-stop.png"));
        }
    });


    // Top layout
    QHBoxLayout *iconLayout = new QHBoxLayout;
    iconLayout->addStretch();
    iconLayout->addWidget(shuffleButton);
    iconLayout->addWidget(backButton);
    iconLayout->addWidget(stopButton);
    iconLayout->addWidget(nextButton);
    iconLayout->addWidget(repeatButton);
    iconLayout->addStretch();


    // Time Labels
    startTime = new QLabel("00:00");
    startTime->setAlignment(Qt::AlignRight);
    startTime->setStyleSheet("max-width: 30px; color: #EDEDED; padding: 0px;");
    endTime = new QLabel("00:00");
    endTime->setAlignment(Qt::AlignLeft);
    endTime->setStyleSheet("max-width: 30px; color: #EDEDED; padding: 0px;");;

    // Timeline music slider
    musicTimeline = new MusicSlider();
    musicTimeline->setFixedHeight(5);
    musicTimeline->setRange(0, 10000);
    musicTimeline->setMinimumWidth(100);
    musicTimeline->setMaximumWidth(700);
    musicTimeline->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    musicTimeline->setStyleSheet("QSlider::groove:horizontal { margin: 2px; background: #A5A5A5; height: 5px; }"
            "QSlider::handle:horizontal { background: transparent; }"
            "QSlider::sub-page:horizontal { background: #EDEDED; }");
    endTime->connect(musicTimeline, &MusicSlider::secondChanged, [this](int currentMusicTimeLineValue){
        int seconds = static_cast<int>(currentMusicTimeLineValue / 100);
        int minutes = seconds / 60;
        seconds = seconds % 60;

        QString strMinutes = QString::number(minutes);
        QString strSeconds = QString::number(seconds);
        this->startTime->setText(strMinutes + ":" + ((strSeconds.length() == 1) ? "0" + strSeconds : strSeconds));
    });


    // Connect event of changing track to all necesary widgets
    connect(Globals::player, &Player::trackChanged, [this](){
        if (Globals::player->isCurrentTrackLoaded() == false) return;

        std::shared_ptr<MusicObject> curMusic = Globals::player->getCurrentMusic();

        this->authorLabel->setText(curMusic->getAuthor());
        this->nameLabel->setText(curMusic->getName());

        QString minutes = QString::number(Globals::player->getDuration() / 60);
        QString seconds = QString::number(Globals::player->getDuration() % 60);
        this->endTime->setText(minutes + ":" + ((seconds.length() == 1) ? "0" + seconds : seconds));
        this->startTime->setText("00:00");

        this->musicTimeline->setRange(0, Globals::player->getDuration() * 100);
        this->musicTimeline->setValue(0);

        if(Globals::player->getCurrentMusic()->getProfilePath() != "") {
            HttpClient::sendGetRequest(QUrl(Env::get("SERVER_DOMEN") + "/music/getProfile?path=" + Globals::player->getCurrentMusic()->getProfilePath()),
                [this](HttpClient::Response* response) {
                if (response->statusCode < 400) {
                    QPixmap pixmap;
                    pixmap.loadFromData(response->body);
                    this->musicImage->setIcon(QIcon(pixmap));
                }
            });
        }
    });


    // Bottom layout
    QHBoxLayout *timelineLayout = new QHBoxLayout;
    timelineLayout->addWidget(startTime);
    timelineLayout->addWidget(musicTimeline);
    timelineLayout->addWidget(endTime);
    timelineLayout->setAlignment(Qt::AlignCenter);


    // Second inner layout
    QVBoxLayout *secondInnerLayout = new QVBoxLayout;
    secondInnerLayout->addLayout(iconLayout);
    secondInnerLayout->addLayout(timelineLayout);


    // --- Third inner section

    // Sound button
    soundButton = new SoundButton;
    soundButton->setFixedSize(40, 40);
    soundButton->setStyleSheet("background: inherit");
    soundButton->connect(soundButton, QPushButton::clicked, [this](){
        if (this->soundButton->isButtonClicked() == false) {
            this->soundButton->setPreviousVolumeLevel(Globals::player->getVolumeLevel());
            Globals::player->setVolumeLevel(0);
            this->volumeSlider->setValue(0);
        } else {
            Globals::player->setVolumeLevel(this->soundButton->getPreviousVolumeLevel());
            this->volumeSlider->setValue(this->soundButton->getPreviousVolumeLevel());
        }
        this->soundButton->swapStage();
    });


    // Volume slider
    volumeSlider = new VolumeSlider(Qt::Horizontal);
    volumeSlider->setValue(100);
    volumeSlider->setFixedHeight(5);
    volumeSlider->setFixedWidth(60);
    volumeSlider->setStyleSheet("QSlider::groove:horizontal { background: #A5A5A5; height: 5px; max-width: 80; }"
            "QSlider::handle:horizontal { background: transparent; }"
            "QSlider::sub-page:horizontal { background: #EDEDED; }");


    // Third inner layout
    QHBoxLayout *thirdInnerLayout = new QHBoxLayout;
    thirdInnerLayout->addWidget(soundButton);
    thirdInnerLayout->addWidget(volumeSlider);
    thirdInnerLayout->setSpacing(0);
    thirdInnerLayout->setContentsMargins(3, 0, 0, 0);


    // --- Main Template
    QHBoxLayout *mainLayout = new QHBoxLayout;
    firstInnerLayout->setAlignment(Qt::AlignLeft);
    secondInnerLayout->setAlignment(Qt::AlignCenter);
    thirdInnerLayout->setAlignment(Qt::AlignRight);
    mainLayout->addLayout(firstInnerLayout, 0);
    mainLayout->addLayout(secondInnerLayout, 2);
    mainLayout->addLayout(thirdInnerLayout, 0);

    this->setLayout(mainLayout);

    if (Globals::player->getCurrentQueueInd() != -1) {
        emit Globals::player->trackChanged();
    }
}
