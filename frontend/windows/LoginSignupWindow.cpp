#include "../headers/components/HoverIconButton.h"
#include "../headers/windows/LoginSignupWindow.h"
#include "../headers/utils/globalVariables.h"
#include "../headers/windows/MainWindow.h"
#include "../headers/utils/UserClasses.h"
#include "../headers/utils/HttpClient.h"
#include "../headers/utils/coverFunks.h"
#include "../headers/utils/EnvFile.h"
#include <QRegularExpressionValidator>
#include <QRegularExpression>
#include <QCryptographicHash>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QSpacerItem>
#include <QLayoutItem>
#include <QJsonObject>
#include <QLineEdit>
#include <QLabel>

LoginSignupWindow::LoginSignupWindow(QWidget *parent) : QWidget(parent) {
    this->setMinimumSize(270, 320);
    this->setMaximumSize(270, 320);

    // Collapse button
    HoverIconButton* collapseButton = new HoverIconButton(QIcon(":/assets/line.png"), QIcon(":/assets/line-active.png"));
    collapseButton->setStyleSheet("background: inherit");
    collapseButton->connect(collapseButton, &QPushButton::clicked, []{Globals::widgetManager->collapseApp();});

    // Exit button
    HoverIconButton* exitButton = new HoverIconButton(QIcon(":/assets/cross.png"), QIcon(":/assets/cross-active.png"));
    exitButton->setStyleSheet("background: inherit; margin: 0px 15px 0px 0px;");
    exitButton->connect(exitButton, &QPushButton::clicked, []{Globals::widgetManager->closeApp();});

    QHBoxLayout* controlButtonsLayout = new QHBoxLayout();
    controlButtonsLayout->setAlignment(Qt::AlignRight);
    controlButtonsLayout->addWidget(collapseButton);
    controlButtonsLayout->addWidget(exitButton);

    mainLayout = new QVBoxLayout();

    QVBoxLayout* windowLayout = new QVBoxLayout(this);
    windowLayout->addLayout(controlButtonsLayout);
    windowLayout->addLayout(mainLayout);

    this->renderLoginWindow();
}

void LoginSignupWindow::renderLoginWindow() {
    QLabel *titleLabel = new QLabel("Войти");
    titleLabel->setAlignment(Qt::AlignCenter);
    titleLabel->setStyleSheet("margin: 35px 0px 10px; font-size: 14px; font-weight: bold; color: white;");


    QLineEdit *loginEdit = new QLineEdit();
    loginEdit->setPlaceholderText("Логин или почта");
    loginEdit->setStyleSheet("margin: 0px 15px 0px 0px; color: white; font-size: 14px; border: none; padding: 2px 5px; background: #121212;");


    QLineEdit *passwordEdit = new QLineEdit();
    passwordEdit->setPlaceholderText("Пароль");
    passwordEdit->setEchoMode(QLineEdit::Password);
    passwordEdit->setStyleSheet("margin: 0px 15px 0px 0px; color: white; font-size: 14px; border: none; padding: 2px 5px; background: #121212;");


    QPushButton *toSignupButton = new QPushButton("Регистрация");
    toSignupButton->setStyleSheet("QPushButton { margin: 3px 0px; color: #EDEDED; font-size: 12px; background: black; }"
            "QPushButton:hover { text-decoration: underline; color: white; }");
    toSignupButton->connect(toSignupButton, &QPushButton::clicked, [this](){
        this->renderSignupWindow();
    });


    QPushButton *forgotButton = new QPushButton("Забыли пароль");
    forgotButton->setStyleSheet("QPushButton { margin: 3px 0px; color: #EDEDED; font-size: 12px; background: black; }"
            "QPushButton:hover { text-decoration: underline; color: white; }");


    QPushButton *loginButton = new QPushButton("Войти");
    loginButton->setStyleSheet("QPushButton { color: white; width: 70px; max-width: 80px; max-height: 30px; padding: 5px; "
            "font-size: 14px; font-weight: bold; background: green; border-radius: 5px; }"
            "QPushButton:hover { color: #EDEDED;  }");
    loginButton->connect(loginButton, &QPushButton::clicked, [this, loginEdit, passwordEdit](){
        this->loginClicked(loginEdit->text(), passwordEdit->text());
    });


    incorrectEdits = new QLabel("");
    incorrectEdits->setStyleSheet("text-align: center; color: red; font-size: 11px; border: none; padding: 5px;");
    incorrectEdits->setAlignment(Qt::AlignCenter);
    incorrectEdits->hide();


    QVBoxLayout *loginMainLayout = new QVBoxLayout();
    loginMainLayout->addWidget(titleLabel);
    loginMainLayout->addWidget(loginEdit);
    loginMainLayout->addWidget(passwordEdit);
    loginMainLayout->addLayout(coverWithHLayout(toSignupButton));
    loginMainLayout->addLayout(coverWithHLayout(forgotButton));
    loginMainLayout->addLayout(coverWithHLayout(loginButton));
    loginMainLayout->addWidget(incorrectEdits);
    loginMainLayout->setAlignment(Qt::AlignTop);


    QLayoutItem *item;
    while ((item = this->mainLayout->takeAt(0)) != nullptr) {
        delete item->widget();
        delete item;
    }
    mainLayout->addWidget(coverLayoutWithWidget(loginMainLayout));
}

void LoginSignupWindow::renderSignupWindow() {
    QLabel *titleLabel = new QLabel("Регистрация");
    titleLabel->setAlignment(Qt::AlignCenter);
    titleLabel->setStyleSheet("margin: 35px 0px 10px; font-size: 14px; font-weight: bold; color: white;");

    QLineEdit *emailEdit = new QLineEdit();
    emailEdit->setPlaceholderText("Почта");
    emailEdit->setStyleSheet("margin: 0px 15px 0px 0px; color: white; font-size: 14px; border: none; padding: 2px 5px; background: #121212;");


    QLineEdit *loginEdit = new QLineEdit();
    loginEdit->setPlaceholderText("Логин");
    loginEdit->setStyleSheet("margin: 0px 15px 0px 0px; color: white; font-size: 14px; border: none; padding: 2px 5px; background: #121212;");


    QLineEdit *passwordEdit = new QLineEdit();
    passwordEdit->setPlaceholderText("Пароль");
    passwordEdit->setEchoMode(QLineEdit::Password);
    passwordEdit->setStyleSheet("margin: 0px 15px 0px 0px; width: 150px; color: white; font-size: 14px; border: none; padding: 2px 5px; background: #121212;");


    QPushButton *toLoginButton = new QPushButton("Войти");
    toLoginButton->setStyleSheet("QPushButton { margin: 3px 0px; color: #EDEDED; font-size: 12px; background: black; }"
            "QPushButton:hover { text-decoration: underline; color: white; }");
    toLoginButton->connect(toLoginButton, &QPushButton::clicked, [this](){
        this->renderLoginWindow();
    });


    QPushButton *signupButton = new QPushButton("Регистрация");
    signupButton->setStyleSheet("QPushButton { color: white; width: 90px; max-height: 30px; padding: 5px; "
           "font-size: 14px; font-weight: bold; background: green; border-radius: 5px; }"
           "QPushButton:hover { color: #EDEDED; }");
    signupButton->connect(signupButton, &QPushButton::clicked, [this, emailEdit, loginEdit, passwordEdit](){
        this->signupClicked(loginEdit->text(), passwordEdit->text(), emailEdit->text());
    });


    incorrectEdits = new QLabel("");
    incorrectEdits->setStyleSheet("text-align: center; color: red; font-size: 11px; border: none; padding: 5px;");
    incorrectEdits->setAlignment(Qt::AlignCenter);
    incorrectEdits->hide();


    QVBoxLayout *signupMainlayout = new QVBoxLayout();
    signupMainlayout->addWidget(titleLabel);
    signupMainlayout->addWidget(emailEdit);
    signupMainlayout->addWidget(loginEdit);
    signupMainlayout->addWidget(passwordEdit);
    signupMainlayout->addLayout(coverWithHLayout(toLoginButton));
    signupMainlayout->addLayout(coverWithHLayout(signupButton));
    signupMainlayout->addWidget(incorrectEdits);
    signupMainlayout->setAlignment(Qt::AlignTop);

    QLayoutItem *item;
    while ((item = this->mainLayout->takeAt(0)) != nullptr) {
        delete item->widget();
        delete item;
    }
    mainLayout->addWidget(coverLayoutWithWidget(signupMainlayout));
}

void LoginSignupWindow::loginClicked(QString credits, QString password) {
    QJsonObject userData;

    if(credits.contains("@")) {
        if(isEmailValid(credits)) {
            userData["email"] = credits;
        } else {
            this->incorrectEdits->setText("Некорректный формат\nпочты");
            this->incorrectEdits->show();
            return;
        }
    } else {
        if(isLoginValid(credits)) {
            userData["login"] = credits;
        } else {
            this->incorrectEdits->setText("Логин некорректный, логин дол-\nжен быть длинной от 2 до 30 символов\nи не должен содержать: \"\'@");
            this->incorrectEdits->show();
            return;
        }
    }

    if(isPasswordValid(password)) {
        userData["password"] = QString::fromUtf8(QCryptographicHash::hash(password.toUtf8(), QCryptographicHash::Sha256).toHex());
    } else {
        this->incorrectEdits->setText("Неверный формат пароля, его\nдлина должна быть от 8 до 30 символов\nи должен содержать хотя бы одну цифру\nодну букву и один спецсимвол");
        this->incorrectEdits->show();
        return;
    }
\
    HttpClient::sendPostRequest(QUrl(Env::get("SERVER_DOMEN") + "/user/auth"), userData, [this](HttpClient::Response* response){
        if(response->statusCode < 400) {
            User::loadUser(response->bodyJsonObj);

            User::setToken(response->bodyJsonObj.value("token").toString());
            User::setRefreshToken(response->bodyJsonObj.value("refreshToken").toString());

            Env::set("TOKEN", User::getToken());
            Env::set("REFRESH_TOKEN", User::getRefreshToken());

            Globals::widgetManager->loadWindow(new MainWindow());
        } else {
            this->incorrectEdits->setText(response->body);
            this->incorrectEdits->show();
        }
    });
}

void LoginSignupWindow::signupClicked(QString login, QString password, QString email) {
    QJsonObject userData;

    if(isEmailValid(email)) {
        userData["email"] = email;
    } else {
        this->incorrectEdits->setText("Некорректный формат\nпочты");
        this->incorrectEdits->show();
        return;
    }

    if(isLoginValid(login)) {
        userData["login"] = login;
    } else {
        this->incorrectEdits->setText("Логин некорректный, логин дол-\nжен быть длинной от 2 до 30 символов\nи не должен содержать: \"\'@");
        this->incorrectEdits->show();
        return;
    }

    if(isPasswordValid(password)) {
        userData["password"] = QString::fromUtf8(QCryptographicHash::hash(password.toUtf8(), QCryptographicHash::Sha256).toHex());
    } else {
        this->incorrectEdits->setText("Неверный формат пароля\nего длина должна быть от 8 до 30 символов\nи должен содержать хотя бы одну цифру\nодну букву и один спецсимвол");
        this->incorrectEdits->show();
        return;
    }

    HttpClient::sendPostRequest(QUrl(Env::get("SERVER_DOMEN") + "/user/reg"), userData, [this](HttpClient::Response* response){
        if(response->statusCode < 400) {
            User::loadUser(response->bodyJsonObj);

            User::setToken(response->bodyJsonObj.value("token").toString());
            User::setRefreshToken(response->bodyJsonObj.value("refreshToken").toString());

            Env::set("TOKEN", User::getToken());
            Env::set("REFRESH_TOKEN", User::getRefreshToken());

            Globals::widgetManager->loadWindow(new MainWindow());
        } else {
            this->incorrectEdits->setText(response->body);
            this->incorrectEdits->show();
        }
    });
}

bool LoginSignupWindow::isPasswordValid(QString password) {
    if(password.length() < 8 && password.length() > 30) return false;

    bool hasLetter = false;
    bool hasDigit = false;
    bool hasSpecial = false;
    QString specialChars = "!@#$%^&*()-_=+[]{}|;:,.<>?/\\`~";

    for (QChar c : password) {
        if (c.isLetter()) {
            hasLetter = true;
        } else if (c.isDigit()) {
            hasDigit = true;
        } else if (specialChars.contains(c)) {
            hasSpecial = true;
        }

        if (hasLetter && hasDigit && hasSpecial) {
            return true;
        }
    }

    return hasLetter && hasDigit && hasSpecial;
}

bool LoginSignupWindow::isLoginValid(QString login) {
    QString invalidSymbols = "'\"@";

    if(login.length() < 2 || login.length() > 30) return false;

    for(QChar ch : login) {
        if(invalidSymbols.contains(ch)) return false;
    }

    return true;
}

bool LoginSignupWindow::isEmailValid(QString email) {
    QRegularExpression emailRegex(R"((^[A-Za-z0-9._%+-]+@[A-Za-z0-9.-]+\.[A-Za-z]{2,}$))");
    QRegularExpressionValidator validator(emailRegex, nullptr);

    int pos = 0;
    return validator.validate(email, pos) == QValidator::Acceptable;
}
