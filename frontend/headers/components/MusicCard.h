#ifndef MUSICCARD_H
#define MUSICCARD_H

#include "../utils/MusicClass.h"
#include <QPushButton>
#include <QLabel>

class MusicCard : public QWidget {
    Q_OBJECT
public:
    explicit MusicCard(std::shared_ptr<MusicObject> musicData, QWidget *parent = nullptr);
private:
    QPushButton* profilePic;
    QPushButton* nameLabel;
    QPushButton* authorLabel;

    std::shared_ptr<MusicObject> musicData;
public slots:
    void trackNameClicked();
    void trackAuthorClicked();
    void trackProfileClicked();
};

#endif // MUSICCARD_H
