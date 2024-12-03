//#include "ui_mainwindow.h"
#include "./headers/utils/globalVariables.h"
#include "headers/app.h"
#include <QMouseEvent>
#include <QIcon>
#include <QRect>

App::App(QWidget* renderingMainWindow, QWidget *parent) : QMainWindow(parent) {
    Globals::widgetManager->connectApp(this);

    // this->setFixedSize(300, 400);
    // LogInWindow *loginWindow = new LogInWindow(this);
    // this->setCentralWidget(loginWindow);

    this->setWindowFlag(Qt::FramelessWindowHint);
    this->setWindowIcon(QIcon(":/assets/windowIcon.png"));
    this->setWindowTitle("MusicBox");
    this->setCentralWidget(renderingMainWindow);
    this->setStyleSheet("background-color: black; padding: 0; margin: 0");
}

App::~App() {}

void App::changeRenderingWidget(QWidget *newRenderingMainWindow) {
    this->setCentralWidget(newRenderingMainWindow);
}

void App::mousePressEvent(QMouseEvent *event) {
    QRect draggableArea(0, 0, width(), 30);
    if (draggableArea.contains(event->pos())) {
        m_dragPosition = event->globalPosition().toPoint() - frameGeometry().topLeft();
        event->accept();
    }
}

void App::mouseMoveEvent(QMouseEvent *event) {
    QRect draggableArea(0, 0, width(), 30);
    if (draggableArea.contains(event->pos())) {
        move(event->globalPosition().toPoint() - m_dragPosition);
        event->accept();
    }
}
