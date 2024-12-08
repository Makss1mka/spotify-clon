#include "../headers/components/HoverIconButton.h"
#include "../headers/windows/LoginSignupWindow.h"
#include "../headers/utils/globalVariables.h"
#include "../headers/pages/MusicAddPage.h"
#include "../headers/utils/UserClasses.h"
#include "../headers/utils/coverFunks.h"
#include "../headers/utils/HttpClient.h"
#include "../headers/utils/EnvFile.h"
#include <QJsonDocument>
#include <QPushButton>
#include <QFileDialog>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QJsonObject>
#include <functional>
#include <QCheckBox>
#include <QLineEdit>
#include <QPointer>
#include <QPixmap>
#include <QDialog>
#include <QLabel>
#include <QSize>
#include <QFile>
#include <QIcon>
#include <QUrl>

MusicAddPage::MusicAddPage(QWidget *parent) : QWidget(parent) {
    this->name = "";
    this->janres = "";
    this->lang = "";
    this->profile = "";
    this->janresList = {
        "Рок", "Поп", "Хип-хоп", "Джаз", "Блюз", "Регги", "Классическая музыка", "Ска", "Рокабилли",
        "Кантри", "Электрическая музыка", "Альтернатива", "Инди", "Метал", "Фолк", "Фьюжн", "Психоделический рок",
        "Латинская музыка", "R&B", "Соул", "Фанк", "Панк-рок", "Гранж", "Готик-рок", "Диско", "Глэм-рок",
        "Хард-рок", "Прогрессивный рок", "Симфонический метал", "Хардкор", "Техно", "Лаунж", "Эмбиент",
        "Транс", "Хаус", "Дабстеп", "Драм-н-бейс", "Трэп", "Трип-хоп", "Ло-фай", "Нью-эйдж", "Чилл-аут",
        "Арт-рок", "Пост-рок", "Ню-метал", "Блэк-метал", "Дэт-метал", "Трэш-метал", "Фолк-метал", "Пауэр-метал",
        "Спид-метал", "Этническая музыка", "Ворлд-мьюзик", "Акапелла", "Шансон", "Техно", "Трэп", "Хардстайл",
        "Евротранс", "Индастриал", "Электро", "Фристайл", "Хэппи-хардкор", "Джангл", "Бритпоп", "Поп-панк",
        "Латино-поп", "Синти-поп", "Ретро", "Кантри-рок", "Альтернативный-рок", "Постпанк", "Гаражный рок", "Мадчестер",
        "Шугейзинг", "Нойз-рок", "Металлкор", "Кранк", "Брейкбит", "Электроника", "Электропоп", "Электро-хаус", "Мумбатон",
        "Прогрессивный хаус", "Хардтехно", "Хардтехно", "Спидкор", "Френчкор", "Кроссовер", "Джаз-фьюжн", "Латиноамериканская музыка",
        "Афробит", "К-Поп", "Джей-поп", "Евротехно", "Евродэнс", "Евродиско", "Рождественская песня", "Баллада", "J-Pop", "Мешап",
        "Арена-рок", "Инди-рок", "Софт-рок"
    };
    this->langsList = {
        "en", "ru", "by", "cn", "de", "fr", "jp", "in", "br", "es", "it", "kr", "pl", "tr"
    };

    // FIRST INNER LAYOUT

    profilePicture = new QPushButton(this);
    profilePicture->setStyleSheet("background: #121212");
    profilePicture->setIcon(QIcon(":/assets/picture.png"));
    profilePicture->setIconSize(QSize(130, 130));

    HoverIconButton* pencilButton = new HoverIconButton(QIcon(":/assets/pencil.png"), QIcon(":/assets/pencil-active.png"));
    pencilButton->setStyleSheet("QPushButton { background: #121212; margin: 0px 0px 40px; padding: 10px 20px; border-radius: 10px; "
            "font-size: 16px; color: white; }"
            "QPushButton:hover { text-decoration: underline; }");
    pencilButton->setText("Добавить иконку");
    pencilButton->setIconSize(QSize(32, 32));
    pencilButton->connect(pencilButton, &QPushButton::clicked, this, &MusicAddPage::addProfileButtonClicked);
    QVBoxLayout* pencilButtonLayout = new QVBoxLayout();
    pencilButtonLayout->setAlignment(Qt::AlignBottom);
    pencilButtonLayout->addWidget(pencilButton);

    QHBoxLayout* firstInnerLayout = new QHBoxLayout();
    firstInnerLayout->setAlignment(Qt::AlignLeft);
    firstInnerLayout->addWidget(profilePicture);
    firstInnerLayout->addLayout(pencilButtonLayout);


    // SECOND INNER LAYOUT

    QLabel* nameLabel = new QLabel("Имя трека: ");
    nameLabel->setStyleSheet("text-align: left; width: 100px; margin: 20px 0px 0px; padding: 0px; font-size: 16px; color: white;");
    nameLabel->setFixedWidth(100);
    nameLineEdit = new QLineEdit();
    nameLineEdit->setPlaceholderText("Введите имя трека");
    nameLineEdit->setFixedWidth(450);
    nameLineEdit->setStyleSheet("color: white; width: 300x; margin: 20px 0px 0px; padding: 0px; font-size: 16px; width: 300px; background: black;");

    QHBoxLayout* secondInnerLayout = new QHBoxLayout();
    secondInnerLayout->setAlignment(Qt::AlignLeft);
    secondInnerLayout->addWidget(nameLabel);
    secondInnerLayout->addWidget(nameLineEdit);


    // THIRD INNER LAYOUT

    QLabel* janressLabel = new QLabel("Выберете жанры");
    janressLabel->setStyleSheet("text-align: left; width: 200px; margin: 20px 0px 0px; padding: 0px; font-size: 13px; color: white;");

    mainJanresLayout = new QHBoxLayout();
    for(int i = 0; i < this->janresList.size() / 12; i++) {
        QVBoxLayout* oneJanresColumn = new QVBoxLayout();

        int len = (((i + 1) * 12) < this->janresList.size()) ? ((i + 1) * 12) : this->janresList.size();
        for(int j = i * 12; j < len; j++) {
            QCheckBox* oneJanre = new QCheckBox(this->janresList[j]);
            oneJanre->setStyleSheet("text-align: left; width: 100px; margin: 0px; padding: 0px; font-size: 11px; color: white;");

            oneJanresColumn->addWidget(oneJanre);
        }
        mainJanresLayout->addLayout(oneJanresColumn);
    }

    QVBoxLayout* thirdInnerLayout = new QVBoxLayout();
    thirdInnerLayout->addWidget(janressLabel);
    thirdInnerLayout->addLayout(mainJanresLayout);

    // FOURTH INNER LAYOUT

    QLabel* langsLabel = new QLabel("Выберете язык");
    langsLabel->setStyleSheet("text-align: left; width: 200px; margin: 20px 0px 0px; padding: 0px; font-size: 13px; color: white;");

    mainLangsLayout = new QHBoxLayout();
    for(int i = 0; i < this->langsList.size() / 3; i++) {
        QVBoxLayout* oneLangColumn = new QVBoxLayout();

        int len = (((i + 1) * 3) < this->langsList.size()) ? ((i + 1) * 3) : this->langsList.size();
        for(int j = i * 3; j < len; j++) {
            QCheckBox* oneJanre = new QCheckBox(this->langsList[j]);
            oneJanre->setStyleSheet("text-align: left; width: 30px; margin: 0px; padding: 0px; font-size: 11px; color: white;");
            oneJanre->connect(oneJanre, &QCheckBox::clicked, [this, oneJanre](){
                for(int i = 0; i < mainLangsLayout->count(); i++) {
                    QVBoxLayout* oneLangColumn = qobject_cast<QVBoxLayout*>(mainLangsLayout->itemAt(i)->layout());

                    for(int j = 0; j < oneLangColumn->count(); j++) {
                        (qobject_cast<QCheckBox*>(oneLangColumn->itemAt(j)->widget()))->setChecked(false);
                    }
                }
                oneJanre->setChecked(true);
            });
            oneLangColumn->addWidget(oneJanre);
        }
        mainLangsLayout->addLayout(oneLangColumn);
    }

    QVBoxLayout* fourthInnerLayout = new QVBoxLayout();
    fourthInnerLayout->addWidget(langsLabel);
    fourthInnerLayout->addLayout(mainLangsLayout);


    // FIFTH INNER LAYOUT

    trackPathName = new QLabel("");
    trackPathName->setStyleSheet("text-align: left; margin: 0px; padding: 0px; font-size: 13px; color: white;");

    HoverIconButton* addMusicPencilButton = new HoverIconButton(QIcon(":/assets/pencil.png"), QIcon(":/assets/pencil-active.png"));
    addMusicPencilButton->setStyleSheet("QPushButton { background: #121212; margin: 0px;"
            "font-size: 13px; color: white; }"
            "QPushButton:hover { text-decoration: underline; }");
    addMusicPencilButton->setText("Добавить файл трека");
    addMusicPencilButton->setIconSize(QSize(26, 26));
    addMusicPencilButton->connect(addMusicPencilButton, &QPushButton::clicked, this, &MusicAddPage::addMusicFileButtonClicked);

    QHBoxLayout* fifthInnerLayout = new QHBoxLayout();
    fifthInnerLayout->setAlignment(Qt::AlignLeft);
    fifthInnerLayout->addWidget(trackPathName);
    fifthInnerLayout->addWidget(addMusicPencilButton);


    // SIXTH INNER LAYOUT

    errorLabel = new QLabel("");
    errorLabel->setStyleSheet("text-align: center; color: red; font-size: 11px; border: none; padding: 5px;");
    errorLabel->hide();

    confirmationButton = new QPushButton("Подтвердить изменения");
    confirmationButton->setStyleSheet("QPushButton { padding: 10px; border-radius: 15px; font-size: 16px; background: green; color: white; font-weight: bold; }"
            "QPushButton:hover { text-decoration: underline; }");
    confirmationButton->connect(confirmationButton, &QPushButton::clicked, this, &MusicAddPage::confirmationButtonClicked);

    declineButton = new QPushButton("Отменить изменения");
    declineButton->setStyleSheet("QPushButton { margin: 0px 15px 0px 0px; padding: 10px; border-radius: 15px; font-size: 16px; background: green; color: white; font-weight: bold; }"
            "QPushButton:hover { text-decoration: underline; }");
    declineButton->connect(declineButton, &QPushButton::clicked, this, &MusicAddPage::declineChangesButtonClicked);

    QHBoxLayout* sixthInnerLayout = new QHBoxLayout();
    sixthInnerLayout->addWidget(errorLabel);
    sixthInnerLayout->addStretch();
    sixthInnerLayout->addWidget(declineButton);
    sixthInnerLayout->addWidget(confirmationButton);


    // MAIN LAYOUT

    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    mainLayout->addLayout(firstInnerLayout);
    mainLayout->addLayout(secondInnerLayout);
    mainLayout->addLayout(thirdInnerLayout);
    mainLayout->addLayout(fourthInnerLayout);
    mainLayout->addLayout(fifthInnerLayout);
    mainLayout->addLayout(sixthInnerLayout);

}

void MusicAddPage::addProfileButtonClicked() {
    QString imagePath = QFileDialog::getOpenFileName(this, "Выберите изображение", "", "Images (*.png *.jpg *.jpeg)");

    if (!imagePath.isEmpty()) {
        this->profileType = imagePath.split(".")[imagePath.split(".").length() - 1];

        QFile file(imagePath);
        if (!file.open(QIODevice::ReadOnly)) {
            qDebug() << "Не удалось открыть файл:" << file.errorString();
            return;
        }

        this->profile = file.readAll();
        file.close();

        QPixmap pixmap;
        pixmap.loadFromData(this->profile);
        this->profilePicture->setIcon(QIcon(pixmap));
    }
}

void MusicAddPage::addMusicFileButtonClicked() {
    QString musicPath = QFileDialog::getOpenFileName(this, "Выберите аудио файл", "", "Audio Files (*.mp3)");

    if (!musicPath.isEmpty()) {
        QFile file(musicPath);
        if (!file.open(QIODevice::ReadOnly)) {
            qDebug() << "Не удалось открыть файл:" << file.errorString();
            return;
        }

        this->trackPathName->setText(musicPath);
        this->musicFile = file.readAll();
        file.close();
    }
}

void MusicAddPage::confirmationButtonClicked() {
    if(User::getRole() != 1) {
        this->errorLabel->setText("Вы не являетесь автором");
        this->errorLabel->show();
        return;
    }
    if(LoginSignupWindow::isLoginValid(this->nameLineEdit->text()) == false) {
        this->errorLabel->setText("Имя трека некорректное, имя дол-\nжно быть длинной от 2 до 30 символов\nи не должен содержать: \"\'@");
        this->errorLabel->show();
        return;
    }
    if(this->musicFile == "") {
        this->errorLabel->setText("Выберете файл песни");
        this->errorLabel->show();
        return;
    }

    QJsonObject musicData;
    musicData["author_id"] = User::getId();
    musicData["name"] = this->nameLineEdit->text();
    musicData["janres"] = "";
    musicData["lang"] = "";

    for(int i = 0; i < mainLangsLayout->count(); i++) {
        QVBoxLayout* oneLangColumn = qobject_cast<QVBoxLayout*>(mainLangsLayout->itemAt(i)->layout());

        for(int j = 0; j < oneLangColumn->count(); j++) {
            QCheckBox* checkBox = qobject_cast<QCheckBox*>(oneLangColumn->itemAt(j)->widget());
            if (checkBox->isChecked() == true) musicData["lang"] = checkBox->text();
        }
    }

    QString janresStr = "";
    for(int i = 0; i < mainJanresLayout->count(); i++) {
        QVBoxLayout* oneJanreColumn = qobject_cast<QVBoxLayout*>(mainJanresLayout->itemAt(i)->layout());

        for(int j = 0; j < oneJanreColumn->count(); j++) {
            QCheckBox* checkBox = qobject_cast<QCheckBox*>(oneJanreColumn->itemAt(j)->widget());
            if (checkBox->isChecked() == true) janresStr += checkBox->text() + ",";
        }
    }
    musicData["janres"] = janresStr;

    if(musicData["janres"] == "") {
        this->errorLabel->setText("Добавьте хотя бы один жанр");
        this->errorLabel->show();
        return;
    }
    if(musicData["lang"] == "") {
        this->errorLabel->setText("Выберете язык песни");
        this->errorLabel->show();
        return;
    }

    HttpClient::sendPostRequest(QUrl(Env::get("SERVER_DOMEN") + "/music/addMusicBasicInfo"), musicData, [this](HttpClient::Response* response) {
        if(response->statusCode < 400) {
            HttpClient::sendPostFileRequest("/music/addMusicFile?music_id=" + QString::number(response->bodyJsonObj.value("music_id").toInt()),
                this->musicFile, "audio/mpeg", [this](int statusCode){
                if(statusCode > 400) {}
            });

            if(this->profile != "") {
                HttpClient::sendPostFileRequest("/music/addMusicProfile?music_id=" + QString::number(response->bodyJsonObj.value("music_id").toInt()),
                    this->profile, "image/" + this->profileType, [this](int statusCode){
                    if(statusCode > 400) {}
                });
            }
        }
    });
}

void MusicAddPage::declineChangesButtonClicked() {

}

