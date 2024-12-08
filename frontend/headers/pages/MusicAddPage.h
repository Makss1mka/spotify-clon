#ifndef MUSICADDPAGE_H
#define MUSICADDPAGE_H

#include <QHBoxLayout>
#include <QPushButton>
#include <QByteArray>
#include <functional>
#include <QLineEdit>
#include <QWidget>
#include <QString>
#include <QDialog>
#include <QLabel>

class MusicAddPage : public QWidget {
    Q_OBJECT
public:
    explicit MusicAddPage(QWidget* parent = nullptr);
private:
    QString name;
    QString janres;
    QString lang;
    QByteArray profile;
    QString profileType;
    QByteArray musicFile;
    std::vector<QString> janresList;
    std::vector<QString> langsList;

    QHBoxLayout* mainJanresLayout;
    QHBoxLayout* mainLangsLayout;

    QPushButton* profilePicture;
    QLabel* trackPathName;
    QLabel* errorLabel;
    QLineEdit* nameLineEdit;

    QPushButton* confirmationButton;
    QPushButton* declineButton;

    void addProfileButtonClicked();
    void addMusicFileButtonClicked();
    void confirmationButtonClicked();
    void declineChangesButtonClicked();
};

#endif // MUSICADDPAGE_H
