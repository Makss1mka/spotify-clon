#ifndef MAININTERACTSECTION_H
#define MAININTERACTSECTION_H

#include <QVBoxLayout>
#include <QScrollArea>
#include <QWidget>

class MainInteractSection : public QWidget {
    Q_OBJECT
public:
    explicit MainInteractSection(QWidget *parent = nullptr);
    virtual ~MainInteractSection() = default;

    void loadPage(QWidget* page);
private:
    QWidget* mainWidget;
    QVBoxLayout* mainLayout;
};

#endif // MAININTERACTSECTION_H
