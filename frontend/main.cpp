#include "./headers/windows/LoginSignupWindow.h"
#include "./headers/windows/MainWindow.h"
#include "./headers/utils/UserClasses.h"
#include "./headers/utils/HttpClient.h"
#include "./headers/utils/EnvFile.h"
#include "./headers/utils/Player.h"
#include "./headers/app.h"
#include <QApplication>
#include <QJsonObject>
#include <QUrl>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    User::setToken(Env::get("TOKEN"));
    User::setRefreshToken(Env::get("REFRESH_TOKEN"));
    qDebug() << User::getToken() << "\n\n" << User::getRefreshToken();
    App* app;

    HttpClient::sendGetRequest(QUrl(Env::get("SERVER_DOMEN") + "/user/authViaToken"), [&app](HttpClient::Response* response) {
        if(response->statusCode < 400) {
            User::loadUser(response->bodyJsonObj);
            App* app = new App(new MainWindow());
            app->show();
        } else if(User::getRefreshToken() != "") {
            HttpClient::sendGetRequest(QUrl(Env::get("SERVER_DOMEN") + "/user/refreshToken"), [&app](HttpClient::Response* response) {
                if(response->statusCode < 400) {
                    User::setToken(response->bodyJsonObj.value("newToken").toString());
                    Env::set("TOKEN", response->bodyJsonObj.value("newToken").toString());

                    HttpClient::sendGetRequest(QUrl(Env::get("SERVER_DOMEN") + "/user/authViaToken"), [&app](HttpClient::Response* response) {
                        if (response->statusCode < 400) {
                            User::loadUser(response->bodyJsonObj);
                            app = new App(new MainWindow());
                            app->show();
                        } else {
                            app = new App(new LoginSignupWindow());
                            app->show();
                        }
                    }, User::getToken());
                } else {
                    app = new App(new LoginSignupWindow());
                    app->show();
                }
            }, User::getRefreshToken());
        } else {
            app = new App(new LoginSignupWindow());
            app->show();
        }
    }, User::getToken());

    // QJsonObject authUserObj;
    // authUserObj["login"] = "rom6ros";
    // authUserObj["password"] = "sigmOID";
    // HttpClient::sendPostRequest(QUrl(Env::get("SERVER_DOMEN") + "/user/auth"), authUserObj, [](HttpClient::Response* response) {
    //     User::loadUser(response->bodyJsonObj);

    //     App* app = new App(new MainWindow());
    //     app->show();
    // });

    return a.exec();
}
