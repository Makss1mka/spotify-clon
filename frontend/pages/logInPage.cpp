#include "../headers/pages/logInPage.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QHBoxLayout>
#include <QSpacerItem>
#include <QFont>

LoginWidget::LoginWidget(QWidget *parent) : QWidget(parent) {
    QFont font = this->font();
    font.setPointSize(14);
    this->setFont(font);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setSpacing(20);

    QLabel *titleLabel = new QLabel("Войти", this);
    titleLabel->setAlignment(Qt::AlignCenter);
    layout->addWidget(titleLabel);

    QLineEdit *loginEdit = new QLineEdit(this);
    loginEdit->setContentsMargins(20, 0, 20, 0);
    loginEdit->setPlaceholderText("login");
    layout->addWidget(loginEdit);

    QLineEdit *passwordEdit = new QLineEdit(this);
    passwordEdit->setContentsMargins(20, 0, 20, 0);
    passwordEdit->setPlaceholderText("password");
    passwordEdit->setEchoMode(QLineEdit::Password);
    layout->addWidget(passwordEdit);

    QLabel *registerLabel = new QLabel("Регистрация", this);
    font.setPointSize(10);
    registerLabel->setFont(font);
    registerLabel->setAlignment(Qt::AlignCenter);
    registerLabel->setTextFormat(Qt::RichText);
    registerLabel->setTextInteractionFlags(Qt::TextBrowserInteraction);
    registerLabel->setOpenExternalLinks(true);
    layout->addWidget(registerLabel);

    QLabel *forgotLabel = new QLabel("Забыли пароль", this);
    forgotLabel->setFont(font);
    forgotLabel->setAlignment(Qt::AlignCenter);
    forgotLabel->setTextFormat(Qt::RichText);
    forgotLabel->setTextInteractionFlags(Qt::TextBrowserInteraction);
    forgotLabel->setOpenExternalLinks(true);
    layout->addWidget(forgotLabel);

    QPushButton *loginButton = new QPushButton("Войти", this);
    loginButton->setFixedWidth(130);
    loginButton->setFixedHeight(55);
    loginButton->setContentsMargins(0, 20, 0, 20);

    QHBoxLayout *loginButtonLayout = new QHBoxLayout();
    loginButtonLayout->addStretch();
    loginButtonLayout->addWidget(loginButton);
    loginButtonLayout->addStretch();
    layout->addLayout(loginButtonLayout);

    layout->addSpacerItem(new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding));
}
