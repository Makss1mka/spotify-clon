#include "./headers/utils/UserClasses.h"
#include "./headers/utils/HttpClient.h"
#include "./headers/utils/EnvFile.h"
#include "./headers/utils/Player.h"
#include "./headers/app.h"
#include <QApplication>
#include <QUrl>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    HttpClient::sendGetRequest(QUrl(Env::get("SERVER_DOMEN", ":/.env") + "/user/auth?login=rom6ros&password=sigmOID"), [](HttpClient::Response* response) {
        User::loadUser(response->bodyJsonObj);

        App* app = new App();
        app->show();
    });

    return a.exec();
}
