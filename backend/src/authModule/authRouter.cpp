#include "../headers/concepts/router.h"
#include "../headers/concepts/Request.h"
#include "../headers/authModule/AuthProvider.h"
#include "../headers/authModule/AuthRouter.h"
#include "../headers/utils/exceptions.h"
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
            throw BadRequestException(
                "Invalid body format for registartion",
                "Invalid body format for registartion"
            );
        }

        std::shared_ptr<AuthProvider> authProvider = this->getProvider<AuthProvider>("authProvider");
        QByteArray data = authProvider->registerUser(request.body["login"], request.body["password"], request.body["email"]);

        QByteArray response = "HTTP/1.1 201 Created\r\n"
                        "Content-Type: text/plain\r\n"
                        "Content-Length: " + QByteArray::number(data.size()) + "\r\n"
                        "\r\n";
        response.append(data);

        return response;
    });

    this->addGetRoute("/auth", [this](Request& request) -> QByteArray {
        if(request.query.size() != 2 || !(request.query.count("login") == 0 ^ request.query.count("email") == 0) || request.query.count("password") == 0) {
            throw BadRequestException(
                "Invalid body format for authorization",
                "Invalid body format for authorization"
            );
        }

        std::shared_ptr<AuthProvider> authProvider = this->getProvider<AuthProvider>("authProvider");
        QByteArray data;

        if (request.query.count("login") == 0) {
            data = authProvider->authUser("", request.query["email"], request.query["password"]);
        } else {
            data = authProvider->authUser(request.query["login"], "", request.query["password"]);
        }

        QByteArray response = "HTTP/1.1 200 OK\r\n"
                        "Content-Type: application/json\r\n"
                        "Content-Length: " + QByteArray::number(data.size()) + "\r\n"
                        "\r\n";
        response.append(data);

        return response;
    });

}

