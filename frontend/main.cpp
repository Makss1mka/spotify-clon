#include "./headers/app.h"
#include "./headers/utils/globalVariables.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    App* app = new App();
    app->show();

    return a.exec();
}
