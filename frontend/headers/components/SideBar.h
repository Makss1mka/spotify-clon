#ifndef SIDEBARH_H
#define SIDEBARH_H

#include <QVBoxLayout>
#include <QPushButton>
#include <QWidget>
#include <QLabel>

class SideBar : public QWidget {
    Q_OBJECT
public:
    explicit SideBar(QWidget *parent = nullptr);

    int getCurrentStage();
private:
    int currentStage;

    QLabel* label;
    QPushButton* musics;
    QPushButton* authors;
    QVBoxLayout* scrollBarLayout;
public slots:
    void musicsClicked();
    void authorsClicked();
};

#endif // SIDEBARH_H
