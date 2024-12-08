#ifndef USERPAGE_H
#define USERPAGE_H

#include <QPushButton>
#include <QByteArray>
#include <functional>
#include <QWidget>
#include <QString>
#include <QDialog>
#include <QLabel>

class UserPage : public QWidget {
    Q_OBJECT
public:
    explicit UserPage(QWidget* parent = nullptr);
private:
    QDialog* changingDialog(const QString& labelText, const QString& buttonText, const QString& lineEditText, std::function<void(QString, QLabel*, QDialog*)> handler);

    QString newLogin;
    QString newPassword;
    QString newEmail;
    QByteArray newProfile;
    QString newProfileType;

    QPushButton* profilePicture;
    QLabel* userNameLabel;
    QLabel* userPasswordLabel;
    QLabel* userEmailLabel;

    QPushButton* confirmationButton;
    QPushButton* declineButton;

    bool isProfileExist;
    bool isPasswordChanged;

    void editUsernameButtonClicked();
    void editPasswordButtonClicked();
    void editEmailButtonClicked();
    void editProfileButtonClicked();
    void acceptChangesButtonClicked();
    void declineChangesButtonClicked();
};

#endif // USERPAGE_H
