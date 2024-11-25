#ifndef SIDEBARH_H
#define SIDEBARH_H

#include <QPushButton>
#include <QWidget>
#include <QLabel>

class SideBar : public QWidget {
    Q_OBJECT
public:
    explicit SideBar(QWidget *parent = nullptr);
private:
    QLabel* label;
    QPushButton* musics;
    QPushButton* authors;
};

#endif // SIDEBARH_H
