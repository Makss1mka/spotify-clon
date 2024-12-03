#ifndef APP_H
#define APP_H

#include <QMainWindow>
#include <QMouseEvent>
#include <QWidget>
#include <QObject>
#include <QPoint>
#include <QEvent>

class App : public QMainWindow {
    Q_OBJECT
public:
    App(QWidget* renderingMainWindow, QWidget *parent = nullptr);
    ~App();

    void changeRenderingWidget(QWidget* newRenderingMainWindow);
protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
private:
    QPoint m_dragPosition;
};

#endif // APP_H
