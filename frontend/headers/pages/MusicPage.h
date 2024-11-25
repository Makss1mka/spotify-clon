#ifndef MUSICPAGE_H
#define MUSICPAGE_H

#include "../components/HoverIconButtonWithStages.h"
#include "../components/AuthorCard.h"
#include "../components/MusicCard.h"
#include <QPushButton>
#include <QWidget>
#include <QLabel>

class MusicPage : public QWidget {
    Q_OBJECT
public:
    explicit MusicPage(QWidget *parent = nullptr);
private:
    QLabel* profilePicture;
    QLabel* type;
    QLabel* name;
    QLabel* metaData;
    QPushButton* playButton;
    HoverIconButtonWithStages* loveButthon;
    QPushButton* optionsButton;

    AuthorCard* authorCard;

    QLabel* recsLabel;
    QLabel* subRecsLabel;
    std::vector<MusicCard*> recs;
};

#endif // MUSICPAGE_H
