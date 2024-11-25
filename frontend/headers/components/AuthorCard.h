#ifndef AUTHORCARD_H
#define AUTHORCARD_H

#include <QPushButton>
#include <QLabel>

class AuthorCard : public QPushButton {
    Q_OBJECT
public:
    explicit AuthorCard(std::shared_ptr<AuthorCard> author, QWidget *parent);
    virtual ~AuthorCard() = default;
private:
    virtual void enterEvent(QEnterEvent *event) override;
    virtual void leaveEvent(QEvent *event) override;

    QLabel* picture;
    QLabel* nameLabel;
    QPushButton* playButton;  
};

#endif // AUTHORCARD_H
