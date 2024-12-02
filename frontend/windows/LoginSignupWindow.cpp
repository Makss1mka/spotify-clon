#include "../headers/windows/LogInWindow.h"
#include "../headers/utils/coverFunks.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QHBoxLayout>
#include <QSpacerItem>
#include <QFont>

LogInWindow::LogInWindow(QWidget *parent) : QWidget(parent) {
    QFont font = this->font();
    font.setPointSize(14);
    this->setFont(font);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setSpacing(20);

    QLabel *titleLabel = new QLabel("Войти", this);
    titleLabel->setAlignment(Qt::AlignCenter);
    layout->addLayout(coverWithHLayout(titleLabel));

    QLineEdit *loginEdit = new QLineEdit(this);
    loginEdit->setContentsMargins(20, 0, 20, 0);
    loginEdit->setPlaceholderText("Логин или почта");
    layout->addLayout(coverWithHLayout(loginEdit));

    QLineEdit *passwordEdit = new QLineEdit(this);
    passwordEdit->setContentsMargins(20, 0, 20, 0);
    passwordEdit->setPlaceholderText("Пароль");
    passwordEdit->setEchoMode(QLineEdit::Password);
    layout->addLayout(coverWithHLayout(passwordEdit));

    QPushButton *registerButton = new QPushButton("Регистрация", this);
    font.setPointSize(10);
    registerButton->setFont(font);

    // registerButton->setAlignment(Qt::AlignCenter);
    // registerLabel->setTextFormat(Qt::RichText);
    // registerLabel->setTextInteractionFlags(Qt::TextBrowserInteraction);
    // registerLabel->setOpenExternalLinks(true);

    layout->addLayout(coverWithHLayout(registerButton));

    QPushButton *forgotButton = new QPushButton("Забыли пароль", this);
    forgotButton->setFont(font);

    // forgotLabel->setAlignment(Qt::AlignCenter);
    // forgotLabel->setTextFormat(Qt::RichText);
    // forgotLabel->setTextInteractionFlags(Qt::TextBrowserInteraction);
    // forgotLabel->setOpenExternalLinks(true);

    layout->addLayout(coverWithHLayout(forgotButton));

    QPushButton *loginButton = new QPushButton("Войти", this);
    loginButton->setFixedWidth(130);
    loginButton->setFixedHeight(55);
    loginButton->setContentsMargins(0, 20, 0, 20);
    layout->addLayout(coverWithHLayout(loginButton));

    layout->addSpacerItem(new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding));
}
