#ifndef LOGINSIGNUPWINDOW_H
#define LOGINSIGNUPWINDOW_H

#include <QVBoxLayout>
#include <QWidget>
#include <QString>
#include <QLabel>

class LoginSignupWindow : public QWidget {
    Q_OBJECT
public:
    explicit LoginSignupWindow(QWidget *parent = nullptr);

    void renderLoginWindow();
    void renderSignupWindow();
    static bool isPasswordValid(QString password);
    static bool isLoginValid(QString login);
    static bool isEmailValid(QString email);

    QVBoxLayout* mainLayout;
    QLabel* incorrectEdits;
public slots:
    void loginClicked(QString credits, QString password);
    void signupClicked(QString login, QString password, QString email);
};

#endif // LOGINSIGNUPWINDOW_H
