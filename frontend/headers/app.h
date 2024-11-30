#ifndef APP_H
#define APP_H

#include <QMainWindow>
#include <QMouseEvent>
#include <QWidget>
#include <QObject>
#include <QPoint>
#include <QEvent>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class App : public QMainWindow {
    Q_OBJECT
public:
    App(QWidget *parent = nullptr);
    ~App();
protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
private:
    Ui::MainWindow *ui;
    QPoint m_dragPosition;
};

#endif // APP_H
