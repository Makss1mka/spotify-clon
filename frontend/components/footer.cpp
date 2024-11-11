#include "../headers/components/Footer.h"
#include "../headers/utils/globalVariables.h"
#include "../headers/utils/Player.h"
#include "../headers/utils/MusicClass.h"
#include "../headers/utils/HttpClient.h"
#include "../headers/components/HoverIconButton.h"
#include "../headers/components/SoundButton.h"
#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPixmap>
#include <QSlider>
#include <QTimer>
#include <QIcon>
#include <QSize>
#include <QMediaPlayer>
#include <QFile>

Footer::Footer(QWidget *parent) : QWidget(parent) {
    this->setFixedHeight(70);

    // --- First inner section

    // Music image
    musicImage = new HoverIconButton(":/assets/picture.png", ":/assets/picture-active.png");
    musicImage->setFixedSize(40, 40);
    musicImage->setIconSize(QSize(34, 34));

    // Music name label
    nameLabel = new QLabel("Test name");
    nameLabel->setStyleSheet("color: white; margin: 0px; padding: 0px;");

    // Music author label
    authorLabel = new QLabel("Test author");
    authorLabel->setStyleSheet("font-size: 11px; color: #CDCDCD; padding: 0px;");

    // Labels layout
    QVBoxLayout *textLayout = new QVBoxLayout;
    textLayout->setSpacing(0);
    textLayout->setContentsMargins(6, 8, 6, 8);
    textLayout->addWidget(nameLabel);
    textLayout->addWidget(authorLabel);

    // Check button
    musicConfigButton = new HoverIconButton(":/assets/check.png", ":/assets/check-active.png");
    musicConfigButton->setFixedSize(22, 22);
    musicConfigButton->setStyleSheet("background: grey; border-radius: 11px;");

    // First inner layout
    QHBoxLayout *firstInnerLayout = new QHBoxLayout;
    firstInnerLayout->addWidget(musicImage);
    firstInnerLayout->addLayout(textLayout);
    firstInnerLayout->addWidget(musicConfigButton);

    // --- Second inner section

    // Shuffle Button
    shuffleButton = new HoverIconButton(":/assets/shuffle.png", ":/assets/shuffle-active.png");
    shuffleButton->setStyleSheet("background: inherit");

    // Back button
    backButton = new HoverIconButton(":/assets/angle-left.png", ":/assets/angle-left-active.png");
    backButton->setStyleSheet("background: inherit");

    // Next Button
    nextButton = new HoverIconButton(":/assets/angle-right.png", ":/assets/angle-right-active.png");
    nextButton->setStyleSheet("background: inherit");

    // Repeat button
    repeatButton = new HoverIconButton(":/assets/repeat.png", ":/assets/repeat-active.png");
    repeatButton->setStyleSheet("background: inherit");
    repeatButton->connect(repeatButton, QPushButton::clicked, [this](){
        if (Globals::player->isOnRepeat() == true) {
            Globals::player->swapRepeating();
            this->repeatButton->setNewActiveIconPath(":/assets/repeat-active.png");
            this->repeatButton->setNewIconPath(":/assets/repeat.png");
        } else {
            Globals::player->pause();
            this->repeatButton->setNewActiveIconPath();
            this->repeatButton->setNewIconPath();
            this->repeatButton->setIcon(QIcon(":/assets/player-stop.png"));
        }
    });

    // Stop button
    stopButton = new QPushButton;
    stopButton->setIcon(QIcon(":/assets/player-stop.png"));
    stopButton->setIconSize(QSize(20, 20));
    stopButton->setFixedSize(30, 30);
    stopButton->setStyleSheet("QPushButton { background: white; border-radius: 15px; }");
    stopButton->connect(stopButton, QPushButton::clicked, [this](){
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
    endTime = new QLabel("00:00");

    // Timeline music slider
    musicTimeline = new QSlider(Qt::Horizontal);
    musicTimeline->setFixedHeight(5);
    musicTimeline->setMinimumWidth(250);
    musicTimeline->setMaximumWidth(700);
    musicTimeline->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    musicTimeline->setStyleSheet("QSlider::groove:horizontal { background: #A5A5A5; height: 5px; }"
            "QSlider::handle:horizontal { background: transparent; }"
            "QSlider::sub-page:horizontal { background: #EDEDED; }");

    // Bottom layout
    QHBoxLayout *timelineLayout = new QHBoxLayout;
    timelineLayout->addWidget(startTime);
    timelineLayout->addWidget(musicTimeline);
    timelineLayout->addWidget(endTime);

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
        if (this->soundButton->isMuted == false) {
            this->soundButton->previousVolumeLevel = Globals::player->getVolumeLevel();
            this->soundButton->isMuted = true;
            this->soundButton->swapActiveIcons();
            Globals::player->setVolumeLevel(0);
        } else {
            this->soundButton->isMuted = false;
            this->soundButton->swapActiveIcons();
            Globals::player->setVolumeLevel(this->soundButton->previousVolumeLevel);
        }
    });

    // Volume slider
    volumeSlider = new QSlider(Qt::Horizontal);
    volumeSlider->setFixedHeight(5);
    volumeSlider->setFixedWidth(60);
    volumeSlider->setStyleSheet("QSlider::groove:horizontal { background: #A5A5A5; height: 5px; max-width: 80; }"
            "QSlider::handle:horizontal { background: transparent; }" //white; width: 6px; height: 6px; margin: -4px 0; border-radius: 2.5px; }"
            "QSlider::sub-page:horizontal { background: #EDEDED; }");

    // Third inner layout
    QHBoxLayout *thirdInnerLayout = new QHBoxLayout;
    thirdInnerLayout->addWidget(soundButton);
    thirdInnerLayout->addWidget(volumeSlider);
    thirdInnerLayout->setSpacing(0);
    thirdInnerLayout->setContentsMargins(3, 0, 0, 0);

    // --- Main Template
    QHBoxLayout *mainLayout = new QHBoxLayout;
    mainLayout->addLayout(firstInnerLayout, 0);
    mainLayout->addStretch(1);
    mainLayout->addLayout(secondInnerLayout, 2);
    mainLayout->addStretch(1);
    mainLayout->addLayout(thirdInnerLayout, 0);

    this->setLayout(mainLayout);
}
