#include "../headers/components/HoverIconButton.h"
#include "../headers/windows/LoginSignupWindow.h"
#include "../headers/utils/globalVariables.h"
#include "../headers/utils/UserClasses.h"
#include "../headers/utils/coverFunks.h"
#include "../headers/utils/HttpClient.h"
#include "../headers/pages/UserPage.h"
#include "../headers/utils/EnvFile.h"
#include <QPushButton>
#include <QFileDialog>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <functional>
#include <QLineEdit>
#include <QPointer>
#include <QPixmap>
#include <QDialog>
#include <QLabel>
#include <QSize>
#include <QFile>
#include <QIcon>

UserPage::UserPage(QWidget *parent) : QWidget(parent) {
    this->isProfileExist = false;
    this->newEmail = "";
    this->newLogin = "";
    this->newPassword = "";
    this->newProfile = "";

    // FIRST INNER LAYOUT

    profilePicture = new QPushButton(this);
    profilePicture->setStyleSheet("background: #121212");
    profilePicture->setIcon(QIcon(":/assets/user.png"));
    profilePicture->setIconSize(QSize(170, 170));
    QPointer<QPushButton> pointedProfilePic = profilePicture;
    if(User::getProfilePath() != "") {
        HttpClient::sendGetRequest(QUrl(Env::get("SERVER_DOMEN") + "/music/getProfile?path=" + User::getProfilePath()),
        [pointedProfilePic](HttpClient::Response* response) {
            if (response->statusCode < 400) {
                if (!pointedProfilePic) return;
                QPixmap pixmap;
                pixmap.loadFromData(response->body);
                pointedProfilePic->setIcon(QIcon(pixmap));
            }
        });
    }

    HoverIconButton* pencilButton = new HoverIconButton(QIcon(":/assets/pencil.png"), QIcon(":/assets/pencil-active.png"));
    pencilButton->setStyleSheet("QPushButton { background: #121212; margin: 0px 0px 40px; padding: 10px 20px; border-radius: 10px; "
            "font-size: 16px; color: white; }"
            "QPushButton:hover { text-decoration: underline; }");
    pencilButton->setText("Изменить иконку");
    pencilButton->setIconSize(QSize(32, 32));
    pencilButton->connect(pencilButton, &QPushButton::clicked, this, &UserPage::editProfileButtpnClicked);
    QVBoxLayout* pencilButtonLayout = new QVBoxLayout();
    pencilButtonLayout->setAlignment(Qt::AlignBottom);
    pencilButtonLayout->addWidget(pencilButton);

    QHBoxLayout* firstInnerLayout = new QHBoxLayout();
    firstInnerLayout->setAlignment(Qt::AlignLeft);
    firstInnerLayout->addWidget(profilePicture);
    firstInnerLayout->addLayout(pencilButtonLayout);


    // SECOND INNER LAYOUT

    QLabel* nameLabel = new QLabel("Имя польователя: ");
    nameLabel->setStyleSheet("text-align: left; width: 100px; margin: 0px; padding: 0px; font-size: 16px; color: white;");
    nameLabel->setFixedWidth(200);
    userNameLabel = new QLabel(User::getName());
    userNameLabel->setStyleSheet("margin: 0px; padding: 0px; font-size: 16px; color: white;");
    HoverIconButton* changeUserNameButton = new HoverIconButton(QIcon(":/assets/pencil.png"), QIcon(":/assets/pencil-active.png"));
    changeUserNameButton->setIconSize(QSize(20, 20));
    changeUserNameButton->setText("Изменить имя пользователя");
    changeUserNameButton->setStyleSheet("QPushButton { text-align: right; background: #121212; margin: 0px; padding: 5px; border-radius: 7px; font-size: 16px; color: white;}"
            "QPushButton:hover { text-decoration: underline; }");
    changeUserNameButton->setFixedWidth(300);
    changeUserNameButton->connect(changeUserNameButton, &QPushButton::clicked, this, &UserPage::editUsernameButtonClicked);

    QHBoxLayout* firstInSecondLayout = new QHBoxLayout();
    firstInSecondLayout->addWidget(nameLabel);
    firstInSecondLayout->addStretch();
    firstInSecondLayout->addWidget(userNameLabel);
    firstInSecondLayout->addStretch();
    firstInSecondLayout->addWidget(changeUserNameButton);


    QLabel* passwordLabel = new QLabel("Пароль: ");
    passwordLabel->setStyleSheet("width: 100px; margin: 0px; padding: 0px; font-size: 16px; color: white;");
    passwordLabel->setFixedWidth(200);
    userPasswordLabel = new QLabel("***************");
    userPasswordLabel->setStyleSheet("margin: 0px; padding: 0px; font-size: 16px; color: white;");
    HoverIconButton* changePasswordButton = new HoverIconButton(QIcon(":/assets/pencil.png"), QIcon(":/assets/pencil-active.png"));
    changePasswordButton->setIconSize(QSize(20, 20));
    changePasswordButton->setText("Изменить пароль");
    changePasswordButton->setStyleSheet("QPushButton { text-align: right; background: #121212; margin: 0px; padding: 5px; border-radius: 7px; font-size: 16px; color: white;}"
            "QPushButton:hover { text-decoration: underline; }");
    changePasswordButton->setFixedWidth(300);
    changePasswordButton->connect(changePasswordButton, &QPushButton::clicked, this, &UserPage::editPasswordButtonClicked);

    QHBoxLayout* secondInSecondLayout = new QHBoxLayout();
    secondInSecondLayout->addWidget(passwordLabel);
    secondInSecondLayout->addStretch();
    secondInSecondLayout->addWidget(userPasswordLabel);
    secondInSecondLayout->addStretch();
    secondInSecondLayout->addWidget(changePasswordButton);



    QLabel* emailLabel = new QLabel("Ваша почта: ");
    emailLabel->setStyleSheet("width: 100px; margin: 0px; padding: 0px; font-size: 16px; color: white;");
    emailLabel->setFixedWidth(200);
    userEmailLabel = new QLabel(User::getEmail());
    userEmailLabel->setStyleSheet("margin: 0px; padding: 0px; font-size: 16px; color: white;");
    HoverIconButton* changeEmailButton = new HoverIconButton(QIcon(":/assets/pencil.png"), QIcon(":/assets/pencil-active.png"));
    changeEmailButton->setIconSize(QSize(20, 20));
    changeEmailButton->setText("Изменить почту");
    changeEmailButton->setStyleSheet("QPushButton { text-align: right; background: #121212; margin: 0px; padding: 5px; border-radius: 7px; font-size: 16px; color: white;}"
            "QPushButton:hover { text-decoration: underline; }");
    changeEmailButton->setFixedWidth(300);
    changeEmailButton->connect(changeEmailButton, &QPushButton::clicked, this, &UserPage::editEmailButtonClicked);

    QHBoxLayout* thirdInSecondLayout = new QHBoxLayout();
    thirdInSecondLayout->addWidget(emailLabel);
    thirdInSecondLayout->addStretch();
    thirdInSecondLayout->addWidget(userEmailLabel);
    thirdInSecondLayout->addStretch();
    thirdInSecondLayout->addWidget(changeEmailButton);


    QVBoxLayout* secondInnerLayout = new QVBoxLayout();
    secondInnerLayout->setAlignment(Qt::AlignTop);
    secondInnerLayout->addLayout(firstInSecondLayout);
    secondInnerLayout->addLayout(secondInSecondLayout);
    secondInnerLayout->addLayout(thirdInSecondLayout);

    // THIRD INNER LAYOUT

    QPushButton* logOutButton = new QPushButton("Выйти из аккаунта");
    logOutButton->setStyleSheet("QPushButton { padding: 10px; border-radius: 15px; font-size: 16px; background: red; color: white; font-weight: bold; }"
            "QPushButton:hover { text-decoration: underline; }");
    logOutButton->connect(logOutButton, &QPushButton::clicked, [this](){
        User::clear();
        Globals::player->stop();
        Globals::widgetManager->loadWindow(new LoginSignupWindow());
    });

    confirmationButton = new QPushButton("Подтвердить изменения");
    confirmationButton->setStyleSheet("QPushButton { padding: 10px; border-radius: 15px; font-size: 16px; background: green; color: white; font-weight: bold; }"
            "QPushButton:hover { text-decoration: underline; }");
    confirmationButton->hide();
    confirmationButton->connect(confirmationButton, &QPushButton::clicked, this, &UserPage::acceptChangesButtonClicked);

    declineButton = new QPushButton("Отменить изменения");
    declineButton->setStyleSheet("QPushButton { margin: 0px 15px 0px 0px; padding: 10px; border-radius: 15px; font-size: 16px; background: green; color: white; font-weight: bold; }"
            "QPushButton:hover { text-decoration: underline; }");
    declineButton->hide();
    declineButton->connect(declineButton, &QPushButton::clicked, this, &UserPage::declineChangesButtonClicked);

    QHBoxLayout* thirdInnerLayout = new QHBoxLayout();
    //thirdInnerLayout->setAlignment(Qt::AlignRight);
    thirdInnerLayout->addWidget(logOutButton);
    thirdInnerLayout->addStretch();
    thirdInnerLayout->addWidget(declineButton);
    thirdInnerLayout->addWidget(confirmationButton);


    // MAIN LAYOUT

    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    mainLayout->addLayout(firstInnerLayout);
    mainLayout->addLayout(secondInnerLayout);
    mainLayout->addLayout(thirdInnerLayout);

}

QDialog* UserPage::changingDialog(const QString& labelText, const QString& buttonText, const QString& lineEditText, std::function<void(QString, QLabel*, QDialog*)> handler) {
    QDialog* dialog = new QDialog();
    dialog->setStyleSheet("background: black;");
    dialog->setWindowIcon(QIcon(":/assets/windowIcon.png"));

    QLabel *label = new QLabel(labelText);
    label->setStyleSheet("margin: 0px; font-size: 14px; font-weight: bold; color: white;");

    QLineEdit *lineEdit = new QLineEdit();
    lineEdit->setPlaceholderText(lineEditText);
    lineEdit->setStyleSheet("margin: 0px; color: white; font-size: 14px; border: none; padding: 2px 5px; background: #121212;");

    QLabel *errorLabel = new QLabel("");
    errorLabel->setStyleSheet("text-align: center; color: red; font-size: 11px; border: none; padding: 5px;");

    QPushButton *actionButton = new QPushButton(buttonText);
    actionButton->setStyleSheet("QPushButton { color: white; max-height: 30px; padding: 5px; "
            "font-size: 14px; font-weight: bold; background: green; border-radius: 5px; }"
            "QPushButton:hover { color: #EDEDED;  }");
    actionButton->connect(actionButton, &QPushButton::clicked, [=](){
        handler(lineEdit->text(), errorLabel, dialog);
    });

    QVBoxLayout *dialogLayout = new QVBoxLayout(dialog);
    dialogLayout->addLayout(coverWithCenterAlign(label));
    dialogLayout->addLayout(coverWithoutStretchHLayout(lineEdit));
    dialogLayout->addLayout(coverWithCenterAlign(actionButton));
    dialogLayout->addLayout(coverWithCenterAlign(errorLabel));

    return dialog;
}

void UserPage::editUsernameButtonClicked() {
    changingDialog("Введите новое имя пользователя", "Новый логин", "Подтвердить изменения" , [this](QString newLogin, QLabel* errorLabel, QDialog* dialog){
        if(LoginSignupWindow::isLoginValid(newLogin) == false) {
            errorLabel->setText("Логин некорректный, логин дол-\nжен быть длинной от 2 до 30 символов\nи не должен содержать: \"\'@");
        } else if (newLogin == User::getName()) {
            if (newPassword == "" && newProfile == "" && newEmail == "") {
                this->confirmationButton->hide();
                this->declineButton->hide();
            }

            this->newLogin = newLogin;
            this->userNameLabel->setText(newLogin);

            dialog->accept();
        } else {
            this->newLogin = newLogin;
            this->userNameLabel->setText(newLogin);
            this->confirmationButton->show();
            this->declineButton->show();

            dialog->accept();
        }
    })->exec();
}

void UserPage::editPasswordButtonClicked() {
    changingDialog("Введите новый пароль", "Новый пароль", "Подтвердить изменения" , [this](QString newPassword, QLabel* errorLabel, QDialog* dialog){
        if(LoginSignupWindow::isPasswordValid(newPassword) == false) {
            errorLabel->setText("Неверный формат пароля, его\nдлина должна быть от 8 до 30 символов\nи должен содержать хотя бы одну цифру\nодну букву и один спецсимвол");
        } else {
            this->newPassword = newPassword;
            this->confirmationButton->show();
            this->declineButton->show();

            dialog->accept();
        }
    })->exec();
}

void UserPage::editEmailButtonClicked() {
    changingDialog("Введите новую почту", "Новая почта", "Подтвердить изменения" , [this](QString newEmail, QLabel* errorLabel, QDialog* dialog){
        if(LoginSignupWindow::isEmailValid(newEmail) == false) {
            errorLabel->setText("Некорректный формат\nпочты");
        } else if (newEmail == User::getEmail()) {
            if (newPassword == "" && newProfile == "" && newLogin == "") {
                this->confirmationButton->hide();
                this->declineButton->hide();
            }

            this->newEmail = newEmail;
            this->userEmailLabel->setText(newEmail);

            dialog->accept();
        } else {
            this->newEmail = newEmail;
            this->userEmailLabel->setText(newEmail);
            this->confirmationButton->show();
            this->declineButton->show();

            dialog->accept();
        }
    })->exec();
}

void UserPage::editProfileButtpnClicked() {
    QString imagePath = QFileDialog::getOpenFileName(this, "Выберите изображение", "", "Images (*.png *.jpg *.jpeg)");

    if (!imagePath.isEmpty()) {
        this->newProfileType = imagePath.split(".")[imagePath.split(".").length() - 1];

        QFile file(imagePath);
        if (!file.open(QIODevice::ReadOnly)) {
            qDebug() << "Не удалось открыть файл:" << file.errorString();
            return;
        }

        this->newProfile = file.readAll();
        file.close();

        QPixmap pixmap;
        pixmap.loadFromData(this->newProfile);
        this->profilePicture->setIcon(QIcon(pixmap));

        this->declineButton->show();
        this->confirmationButton->show();
    }
}

void UserPage::acceptChangesButtonClicked() {
    HttpClient::sendPutNoneJsonRequest(QUrl(Env::get("SERVER_DOMEN") + "/user/updateProfile?user_id=" + QString::number(User::getId())),
        this->newProfile, this->newProfileType, [this](HttpClient::Response* response) {
            if(response->statusCode < 400) {
                if(User::getProfilePath() == "") User::setProfilePath(QString::fromUtf8(response->body));
            }
    });

    QJsonObject userData;
    userData["id"] = User::getId();
    userData["login"] = this->newLogin;
    userData["email"] = this->newEmail;
    userData["password"] = this->newPassword;

    HttpClient::sendPutRequest(QUrl(Env::get("SERVER_DOMEN") + "/user/update"), userData, [this](HttpClient::Response* response){
        if(response->statusCode < 400) {
            User::setName(this->newLogin);
            User::setEmail(this->newEmail);

            this->userNameLabel(this->newLogin);
            this->userEmailLabel(this->newEmail);
        }
    });
}

void UserPage::declineChangesButtonClicked() {
    this->declineButton->hide();
    this->confirmationButton->hide();

    this->newEmail = "";
    this->newLogin = "";
    this->newProfile = "";
    this->newPassword = "";
    this->newProfileType = "";

    this->userNameLabel->setText(User::getName());
    this->userEmailLabel->setText(User::getEmail());

    QPointer<QPushButton> pointedProfilePic = profilePicture;
    if(User::getProfilePath() != "") {
        HttpClient::sendGetRequest(QUrl(Env::get("SERVER_DOMEN") + "/music/getProfile?path=" + User::getProfilePath()),
        [pointedProfilePic](HttpClient::Response* response) {
            if (response->statusCode < 400) {
                if (!pointedProfilePic) return;
                QPixmap pixmap;
                pixmap.loadFromData(response->body);
                pointedProfilePic->setIcon(QIcon(pixmap));
            }
        });
    }
}

