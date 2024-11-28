#ifndef AUTHORCARD_H
#define AUTHORCARD_H

#include "../utils/MusicClass.h"
#include <QPushButton>
#include <QWidget>
#include <QLabel>

class AuthorCard : public QWidget {
    Q_OBJECT
public:
    explicit AuthorCard(std::shared_ptr<AuthorObject> authorData, QWidget *parent = nullptr);
private:
    virtual void enterEvent(QEnterEvent *event) override;
    virtual void leaveEvent(QEvent *event) override;

    QPushButton* profilePic;
    QPushButton* nameLabel;
    QLabel* label ;
    QWidget* mainWidget;

    std::shared_ptr<AuthorObject> authorData;
public slots:
    void trackNameClicked();
    void trackAuthorClicked();
    void trackProfileClicked();
};

#endif // AUTHORCARD_H
