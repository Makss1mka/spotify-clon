#ifndef HEADER_H
#define HEADER_H

#include "./HoverIconButton.h"
#include <QLineEdit>
#include <QWidget>

class Header : public QWidget {
    Q_OBJECT
public:
    explicit Header(QWidget *parent = nullptr);
private:
    HoverIconButton* backButton;
    HoverIconButton* nextButton;

    HoverIconButton* homeButton;
    HoverIconButton* searchButton;
    QLineEdit* searchInputField;

    HoverIconButton* userButton;
    HoverIconButton* collapseButton;
    HoverIconButton* collapseInWindowButton;
    HoverIconButton* exitButton;
};

#endif // HEADER_H
