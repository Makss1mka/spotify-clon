#include "../headers/components/AuthorCard.h"
#include "../headers/utils/MusicClass.h"
#include <QPushButton>
#include <QEnterEvent>
#include <QWidget>


AuthorCard::AuthorCard(std::shared_ptr<AuthorCard> author, QWidget *parent) : QPushButton(parent) {
    setMouseTracking(true);



}

void AuthorCard::enterEvent(QEnterEvent *event) {
    //setStyleSheet();

    QPushButton::enterEvent(event);
}

void AuthorCard::leaveEvent(QEvent *event) {


    QPushButton::leaveEvent(event);
}


