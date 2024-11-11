#include "../headers/components/Player.h"
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

Player::Player(QWidget *parent) : QWidget(parent) {
    this->setFixedHeight(70);

    // First inner section
    musicImage = new QPushButton;
    musicImage->setFixedSize(40, 40);
    musicImage->setIconSize(QSize(34, 34));
    musicImage->setIcon(QIcon(":/assets/picture.png"));

    nameLabel = new QLabel("Test name");
    nameLabel->setStyleSheet("color: white; margin: 0px; padding: 0px;");
    authorLabel = new QLabel("Test author");
    authorLabel->setStyleSheet("font-size: 11px; color: #CDCDCD; padding: 0px;");
    QVBoxLayout *textLayout = new QVBoxLayout;
    textLayout->setSpacing(0);
    textLayout->setContentsMargins(6, 8, 6, 8);
    textLayout->addWidget(nameLabel);
    textLayout->addWidget(authorLabel);

    musicConfigButton = new QPushButton;
    musicConfigButton->setIcon(QIcon(":/assets/check.png"));
    musicConfigButton->setFixedSize(22, 22);
    musicConfigButton->setStyleSheet("background: grey; border-radius: 11px;");

    QHBoxLayout *firstInnerLayout = new QHBoxLayout;
    firstInnerLayout->addWidget(musicImage);
    firstInnerLayout->addLayout(textLayout);
    firstInnerLayout->addWidget(musicConfigButton);

    // Second inner section
    shuffleButton = new QPushButton;
    shuffleButton->setIcon(QIcon(":/assets/shuffle.png"));
    shuffleButton->setStyleSheet("background: inherit");
    backButton = new QPushButton;
    backButton->setIcon(QIcon(":/assets/angle-left.png"));
    backButton->setStyleSheet("background: inherit");
    nextButton = new QPushButton;
    nextButton->setIcon(QIcon(":/assets/angle-right.png"));
    nextButton->setStyleSheet("background: inherit");
    repeatButton = new QPushButton;
    repeatButton->setIcon(QIcon(":/assets/repeat.png"));
    repeatButton->setStyleSheet("background: inherit");
    stopButton = new QPushButton;
    stopButton->setIcon(QIcon(":/assets/player-stop.png"));
    stopButton->setIconSize(QSize(20, 20));
    stopButton->setFixedSize(30, 30);
    stopButton->setStyleSheet("background: white; border-radius: 15px;");

    QHBoxLayout *iconLayout = new QHBoxLayout;
    iconLayout->addStretch();
    iconLayout->addWidget(shuffleButton);
    iconLayout->addWidget(backButton);
    iconLayout->addWidget(stopButton);
    iconLayout->addWidget(nextButton);
    iconLayout->addWidget(repeatButton);
    iconLayout->addStretch();

    startTime = new QLabel("00:00");
    endTime = new QLabel("00:00");

    musicTimeline = new QSlider(Qt::Horizontal);
    musicTimeline->setFixedHeight(5);
    musicTimeline->setMinimumWidth(250);
    musicTimeline->setMaximumWidth(700);
    musicTimeline->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    musicTimeline->setStyleSheet("QSlider::groove:horizontal { background: #A5A5A5; height: 5px; }"
            "QSlider::handle:horizontal { background: transparent; }"
            "QSlider::sub-page:horizontal { background: #EDEDED; }");

    timelineCircle = new QLabel;
    timelineCircle->setFixedSize(14, 14);
    timelineCircle->setStyleSheet("background: grey; border-radius: 7px;");
    timelineCircle->hide();

    QHBoxLayout *timelineLayout = new QHBoxLayout;
    timelineLayout->addWidget(startTime);
    timelineLayout->addWidget(musicTimeline);
    timelineLayout->addWidget(endTime);

    QVBoxLayout *secondInnerLayout = new QVBoxLayout;
    secondInnerLayout->addLayout(iconLayout);
    secondInnerLayout->addLayout(timelineLayout);

    // Third inner section
    soundButton = new QPushButton;
    soundButton->setIcon(QIcon(":/assets/sound.png"));
    soundButton->setFixedSize(40, 40);
    soundButton->setStyleSheet("background: inherit");

    volumeSlider = new QSlider(Qt::Horizontal);
    volumeSlider->setFixedHeight(5);
    volumeSlider->setFixedWidth(60);
    volumeSlider->setStyleSheet("QSlider::groove:horizontal { background: #A5A5A5; height: 5px; max-width: 80; }"
            "QSlider::handle:horizontal { background: transparent; }" //white; width: 6px; height: 6px; margin: -4px 0; border-radius: 2.5px; }"
            "QSlider::sub-page:horizontal { background: #EDEDED; }");

    QHBoxLayout *thirdInnerLayout = new QHBoxLayout;
    thirdInnerLayout->addWidget(soundButton);
    thirdInnerLayout->addWidget(volumeSlider);
    thirdInnerLayout->setSpacing(0);
    thirdInnerLayout->setContentsMargins(3, 0, 0, 0);

    // Main Template
    QHBoxLayout *mainLayout = new QHBoxLayout;
    mainLayout->addLayout(firstInnerLayout, 0);
    mainLayout->addStretch(1);
    mainLayout->addLayout(secondInnerLayout, 2);
    mainLayout->addStretch(1);
    mainLayout->addLayout(thirdInnerLayout, 0);

    this->setLayout(mainLayout);

    //timelineUpdateTimer = new QTimer(this);
    //connect(timelineUpdateTimer, &QTimer::timeout, this, &Player::updateMusicTimeline);
    //timelineUpdateTimer->start(1000);

}

void Player::updateMusicTimeline() {
    int duration = 300;
    int currentTime = musicTimeline->value();
    int percentage = (currentTime * 100) / duration;
    musicTimeline->setValue(percentage);
}
