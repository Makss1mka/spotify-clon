#ifndef MUSICPAGE_H
#define MUSICPAGE_H

#include "../components/HoverIconButtonWithStages.h"
#include "../components/AuthorCard.h"
#include "../components/MusicCard.h"
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>
#include <QLabel>

class MusicPage : public QWidget {
    Q_OBJECT
public:
    explicit MusicPage(std::shared_ptr<MusicObject> musicData, QWidget *parent = nullptr);
private:
    QPushButton* profile;
    QLabel* type;
    QLabel* name;
    QLabel* metaData;
    QPushButton* playButton;
    HoverIconButtonWithStages* loveButton;
    QPushButton* optionsButton;
    std::shared_ptr<MusicObject> musicData;

    AuthorCard* authorCard;

    QVBoxLayout* thirdInnerLayout;

    QLabel* recsLabel;
    QLabel* subRecsLabel;
};

#endif // MUSICPAGE_H
