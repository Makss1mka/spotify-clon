#include "./headers/mainwindow.h"
#include "ui_mainwindow.h"
#include "./headers/pages/logInPage.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    this->setFixedSize(300, 400);

    LoginWidget *loginWidget = new LoginWidget(this);
    this->setCentralWidget(loginWidget);
}

MainWindow::~MainWindow() {
    delete ui;
}
