#include "ui_mainwindow.h"
#include "headers/app.h"
#include "./headers/windows/SignUpWindow.h"
#include "./headers/windows/LogInWindow.h"
#include "./headers/windows/MainWindow.h"

App::App(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    // this->setFixedSize(300, 400);
    // LogInWindow *loginWindow = new LogInWindow(this);
    // this->setCentralWidget(loginWindow);

    this->setMinimumSize(600, 500);
    this->setCentralWidget(new MainWindow(this));
    this->setStyleSheet("background-color: black; padding: 0; margin: 0");
}

App::~App() {
    delete ui;
}
