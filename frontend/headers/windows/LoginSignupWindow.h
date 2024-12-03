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

    QVBoxLayout* mainLayout;
    QLabel* incorrectEdits;
private:
    bool isPasswordValid(QString password);
    bool isLoginValid(QString login);
    bool isEmailValid(QString email);
public slots:
    void loginClicked(QString credits, QString password);
    void signupClicked(QString login, QString password, QString email);
};

#endif // LOGINSIGNUPWINDOW_H
