#include "../headers/windows/SignUpWindow.h"
#include "../headers/utils/coverFunks.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QHBoxLayout>
#include <QSpacerItem>
#include <QFont>

SignUpWindow::SignUpWindow(QWidget *parent) : QWidget(parent) {
    QFont font = this->font();
    font.setPointSize(14);
    this->setFont(font);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setSpacing(20);

    QLabel *titleLabel = new QLabel("Регистрация", this);
    titleLabel->setAlignment(Qt::AlignCenter);
    layout->addWidget(titleLabel);

    QLineEdit *emailEdit = new QLineEdit(this);
    emailEdit->setContentsMargins(20, 0, 20, 0);
    emailEdit->setPlaceholderText("Почта");
    emailEdit->setEchoMode(QLineEdit::Password);
    layout->addWidget(emailEdit);

    QLineEdit *loginEdit = new QLineEdit(this);
    loginEdit->setContentsMargins(20, 0, 20, 0);
    loginEdit->setPlaceholderText("Логин");
    layout->addWidget(loginEdit);

    QLineEdit *passwordEdit = new QLineEdit(this);
    passwordEdit->setContentsMargins(20, 0, 20, 0);
    passwordEdit->setPlaceholderText("Пароль");
    passwordEdit->setEchoMode(QLineEdit::Password);
    layout->addWidget(passwordEdit);

    QPushButton *registerButton = new QPushButton("Войти", this);
    font.setPointSize(10);
    registerButton->setFont(font);
    layout->addLayout(coverWithHLayout(registerButton));

    QPushButton *loginButton = new QPushButton("Регистрация", this);
    loginButton->setFixedWidth(130);
    loginButton->setFixedHeight(55);
    loginButton->setContentsMargins(0, 20, 0, 20);
    layout->addLayout(coverWithHLayout(loginButton));

    layout->addSpacerItem(new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding));
}
