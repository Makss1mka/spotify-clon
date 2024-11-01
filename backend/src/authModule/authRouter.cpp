#include "../headers/concepts/router.h"
#include "../headers/concepts/Request.h"
#include "../headers/authModule/AuthProvider.h"
#include "../headers/authModule/AuthRouter.h"
#include <QByteArray>
#include <QFile>
#include <QString>

AuthRouter::AuthRouter() : Router("/auth") {
    this->setupRoutes();
    this->setupProviders();
}

void AuthRouter::setupProviders() {
    this->addProvider("authProvider", std::make_shared<AuthProvider>());
}

void AuthRouter::setupRoutes() {
    this->addPostRoute("/reg", [this](Request& request) -> QByteArray {
        if(request.body.size() != 3 || request.body.count("login") == 0 || request.body.count("password") == 0 || request.body.count("email") == 0) {
            QByteArray response = "HTTP/1.1 400 Bad Request\r\n"
                        "Content-Type: text/plain\r\n"
                        "Content-Length: 36\r\n"
                        "\r\n"
                        "Invalid body format for registartion";
            return response;
        }

        std::shared_ptr<AuthProvider> authProvider = this->getProvider<AuthProvider>("authProvider");
        QByteArray data = authProvider->registerUser(request.body["login"], request.body["password"], request.body["email"]);
        QByteArray response;

        if(data == "") {
            response = "HTTP/1.1 503 Service Unavailable\r\n"
                        "Content-Type: text/plain\r\n"
                        "Content-Length: 48\r\n"
                        "\r\n"
                        "Authorization service is temporarily unavailable";
        } else if (data == "0") {
            response = "HTTP/1.1 201 Created\r\n"
                        "Content-Type: text/plain\r\n"
                        "Content-Length: " + QByteArray::number(data.size()) + "\r\n"
                        "\r\n";
            response.append(data);
        } else {
            response = "HTTP/1.1 409 Conflict\r\n"
                        "Content-Type: text/plain\r\n"
                        "Content-Length: " + QByteArray::number(data.size()) + "\r\n"
                        "\r\n";
            response.append(data);
        }
        return response;
    });

    this->addGetRoute("/auth", [this](Request& request) -> QByteArray {
        if(request.query.size() != 2 || !(request.query.count("login") == 0 ^ request.query.count("email") == 0) || request.query.count("password") == 0) {
            QByteArray response = "HTTP/1.1 400 Bad Request\r\n"
                        "Content-Type: text/plain\r\n"
                        "Content-Length: 37\r\n"
                        "\r\n"
                        "Invalid body format for authorization";
            return response;
        }

        std::shared_ptr<AuthProvider> authProvider = this->getProvider<AuthProvider>("authProvider");
        QByteArray data;
        QByteArray response;
        QString emptyStr = "";

        if (request.query.count("login") == 0) {
            data = authProvider->authUser(emptyStr, request.query["email"], request.query["password"]);
        } else {
            data = authProvider->authUser(request.query["login"], emptyStr, request.query["password"]);
        }

        if(data == "503") {
            response = "HTTP/1.1 503 Service Unavailable\r\n"
                        "Content-Type: text/plain\r\n"
                        "Content-Length: 48\r\n"
                        "\r\n"
                        "Authorization service is temporarily unavailable";
        } else if (data == "401") {
            response = "HTTP/1.1 401 Unauthorized\r\n"
                       "Content-Type: text/plain\r\n"
                       "Content-Length: 27\r\n"
                       "\r\n"
                       "Invalid account credentials";
        } else {
            response = "HTTP/1.1 200 OK\r\n"
                        "Content-Type: application/json\r\n"
                        "Content-Length: " + QByteArray::number(data.size()) + "\r\n"
                        "\r\n";
            response.append(data);
        }
        return response;
    });

}

