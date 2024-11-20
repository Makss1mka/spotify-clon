#ifndef AUTHORCARD_H
#define AUTHORCARD_H

#include <QPushButton>
#include <QLabel>

class AuthorCard : public QPushButton {
    Q_OBJECT
public:
    explicit AuthorCard(QWidget *parent = nullptr);
private:
    QLabel* picture;
    QLabel* nameLabel;
    QPushButton* playButton;


};

#endif // AUTHORCARD_H
