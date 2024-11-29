#ifndef AUTHORPAGE_H
#define AUTHORPAGE_H

#include "../components/HoverIconButtonWithStages.h"
#include "../utils/MusicClass.h"
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>
#include <QLabel>

class AuthorPage : public QWidget {
    Q_OBJECT
public:
    explicit AuthorPage(std::shared_ptr<AuthorObject> authorData, QWidget *parent = nullptr);
private:
    QPushButton* profileBac;
    QLabel* type;
    QLabel* name;
    QLabel* metaData;
    QPushButton* playButton;
    HoverIconButtonWithStages* loveButton;
    QPushButton* optionsButton;
    std::shared_ptr<AuthorObject> authorData;

    QVBoxLayout* thirdInnerLayout;

    QLabel* popularTracks;
};

#endif // AUTHORPAGE_H
