#include "./headers/app.h"
#include "./headers/utils/globalVariables.h"
#include "./headers/utils/UserClasses.h"
#include "./headers/utils/HttpClient.h"
#include <QApplication>
#include <QUrl>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Globals::httpClient->sendGetRequest(QUrl("http://localhost:3000/user/auth?login=rom6ros&password=sigmOID"), [](const HttpClient::Response& response) {
        User::loadUser(response.bodyJsonObj);

        App* app = new App();
        app->show();
    });

    return a.exec();
}
