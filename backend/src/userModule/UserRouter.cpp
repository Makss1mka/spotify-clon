#include "../headers/concepts/router.h"
#include "../headers/concepts/Request.h"
#include "../headers/userModule/UserProvider.h"
#include "../headers/userModule/UserRouter.h"
#include "../headers/utils/exceptions.h"
#include <QByteArray>
#include <QFile>
#include <QString>

UserRouter::UserRouter() : Router("/user") {
    this->setupRoutes();
    this->setupProviders();
}

void UserRouter::setupProviders() {
    this->addProvider("userProvider", std::make_shared<UserProvider>());
}

void UserRouter::setupRoutes() {
    this->addPostRoute("/reg", [this](Request& request) -> QByteArray {
        if(request.body.size() != 3 || request.body.count("login") == 0 || request.body.count("password") == 0 || request.body.count("email") == 0) {
            throw BadRequestException(
                "Invalid body format for registartion",
                "Invalid body format for registartion"
            );
        }

        std::shared_ptr<UserProvider> userProvider = this->getProvider<UserProvider>("userProvider");
        QByteArray data = userProvider->registerUser(request.body["login"], request.body["password"], request.body["email"]);

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

        std::shared_ptr<UserProvider> userProvider = this->getProvider<UserProvider>("userProvider");
        QByteArray data;

        if (request.query.count("login") == 0) {
            data = userProvider->authUser("", request.query["email"], request.query["password"]);
        } else {
            data = userProvider->authUser(request.query["login"], "", request.query["password"]);
        }

        QByteArray response = "HTTP/1.1 200 OK\r\n"
                        "Content-Type: application/json\r\n"
                        "Content-Length: " + QByteArray::number(data.size()) + "\r\n"
                        "\r\n";
        response.append(data);

        return response;
    });

    this->addUpdateRoute("/update", [this](Request& request) -> QByteArray {
        if(request.query.size() != 5 || request.query.count("login") == 0 || request.query.count("email") == 0
            || request.query.count("password") == 0 || request.query.count("role") == 0 || request.query.count("id") == 0) {
            throw BadRequestException(
                "Invalid body format for update user info",
                "Invalid body format for update user info"
            );
        }

        std::shared_ptr<UserProvider> userProvider = this->getProvider<UserProvider>("userProvider");

        userProvider->updateBasicInfo(request.query["id"], request.query["login"], request.query["email"],
            request.query["password"], request.query["role"]);

        QByteArray response = "HTTP/1.1 200 OK\r\n"
                            "Content-Type: text/plain\r\n"
                            "Content-Length: 33\r\n"
                            "\r\n"
                            "User data was successfuly changed";

        return response;
    });
}

