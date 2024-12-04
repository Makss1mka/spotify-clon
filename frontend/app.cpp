#include "./headers/utils/globalVariables.h"
#include "headers/app.h"
#include <QMouseEvent>
#include <QLayoutItem>
#include <QVBoxLayout>
#include <QWidget>
#include <QIcon>
#include <QSize>
#include <QRect>

App::App(QWidget* renderingMainWindow, QWidget *parent) : QMainWindow(parent) {
    Globals::widgetManager->connectApp(this);

    appMainLayout = new QVBoxLayout();
    QWidget* mainWidget = new QWidget();
    mainWidget->setLayout(appMainLayout);

    this->setWindowFlag(Qt::FramelessWindowHint);
    this->setWindowIcon(QIcon(":/assets/windowIcon.png"));
    this->setWindowTitle("MusicBox");
    this->setCentralWidget(mainWidget);
    this->changeRenderingWidget(renderingMainWindow);
    this->setStyleSheet("background-color: black; padding: 0px; margin: 0px;");
}

App::~App() {}

void App::changeRenderingWidget(QWidget *newRenderingMainWindow) {
    QLayoutItem *item;
    while ((item = this->appMainLayout->takeAt(0)) != nullptr) {
        delete item->widget();
        delete item;
    }

    this->appMainLayout->addWidget(newRenderingMainWindow);
    this->showNormal();
    this->setFixedSize(QSize(newRenderingMainWindow->width(), newRenderingMainWindow->height()));
}

void App::mousePressEvent(QMouseEvent *event) {
    QRect draggableArea(0, 0, width(), 30);
    if (draggableArea.contains(event->pos())) {
        this->showNormal();
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
