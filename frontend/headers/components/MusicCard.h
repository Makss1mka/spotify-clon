#ifndef MUSICCARD_H
#define MUSICCARD_H

#include "../utils/MusicClass.h"
#include <QPushButton>
#include <QEnterEvent>
#include <QWidget>
#include <QEvent>
#include <QLabel>

class MusicCard : public QWidget {
    Q_OBJECT
public:
    explicit MusicCard(std::shared_ptr<MusicObject> musicData, QWidget *parent = nullptr);
private:
    virtual void enterEvent(QEnterEvent *event) override;
    virtual void leaveEvent(QEvent *event) override;

    QPushButton* profilePic;
    QPushButton* nameLabel;
    QPushButton* authorLabel;
    QWidget* mainWidget;

    std::shared_ptr<MusicObject> musicData;
public slots:
    void trackNameClicked();
    void trackAuthorClicked();
    void trackProfileClicked();
};

#endif // MUSICCARD_H
