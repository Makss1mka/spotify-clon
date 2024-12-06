#include "../headers/userModule/UserProvider.h"
#include "../headers/userModule/UserRouter.h"
#include "../headers/utils/exceptions.h"
#include "../headers/concepts/Request.h"
#include "../headers/concepts/router.h"
    #include "../headers/concepts/JWT.h"
    #include "../headers/utils/envFile.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QByteArray>
#include <QString>
#include <QFile>

UserRouter::UserRouter() : Router("/user") {
    this->setupRoutes();
    this->setupProviders();
}

void UserRouter::setupProviders() {
    this->addProvider("userProvider", std::make_shared<UserProvider>());
}

void UserRouter::setupRoutes() {
    this->addPostRoute("/reg", [this](Request& request) -> QByteArray {
        if(request.isBodyJsonObj == false || request.bodyJsonObj.size() != 3 || request.bodyJsonObj.contains("login") == false
            || request.bodyJsonObj.contains("password") == false || request.bodyJsonObj.contains("email") == false) {
            throw BadRequestException(
                "Invalid body format for registartion",
                "Invalid body format for registartion"
            );
        }
        if (request.bodyJsonObj.value("login").isString() == false || request.bodyJsonObj.value("password").isString() == false
            || request.bodyJsonObj.value("email").isString() == false) {
            throw BadRequestException(
                "Invalid body format for registartion, unsupported types",
                "Invalid body format for registartion, unsupported types"
            );
        }

        std::shared_ptr<UserProvider> userProvider = this->getProvider<UserProvider>("userProvider");
        QByteArray data = userProvider->registerUser(request.bodyJsonObj.value("login").toString(),
                request.bodyJsonObj.value("email").toString(),
                request.bodyJsonObj.value("password").toString());

        QByteArray response = "HTTP/1.1 201 Created\r\n"
                        "Content-Type: application/json\r\n"
                        "Content-Length: " + QByteArray::number(data.size()) + "\r\n"
                        "\r\n";
        response.append(data);

        return response;
    });

    this->addPostRoute("/auth", [this](Request& request) -> QByteArray {
        if(request.isBodyJsonObj == false || request.bodyJsonObj.size() != 2 || !(request.bodyJsonObj.contains("login") == false
            ^ request.bodyJsonObj.contains("email") == false) || request.bodyJsonObj.contains("password") == false) {
            throw BadRequestException(
                "Invalid body format for authorization via credits",
                "Invalid body format for authorization via credits"
            );
        }
        if ((request.bodyJsonObj.contains("login") == true && request.bodyJsonObj.value("login").isString() == false)
            || (request.bodyJsonObj.contains("email") == true && request.bodyJsonObj.value("email").isString() == false)
            || request.bodyJsonObj.value("password").isString() == false) {
            throw BadRequestException(
                "Invalid body format for authorization via credits, unsupported types",
                "Invalid body format for authorization via credits, unsupported types"
            );
        }

        std::shared_ptr<UserProvider> userProvider = this->getProvider<UserProvider>("userProvider");
        QByteArray data;

        if (request.bodyJsonObj.contains("login") == false) {
            data = userProvider->authUser("", request.bodyJsonObj.value("email").toString(), request.bodyJsonObj.value("password").toString());
        } else {
            data = userProvider->authUser(request.bodyJsonObj.value("login").toString(), "", request.bodyJsonObj.value("password").toString());
        }

        QByteArray response = "HTTP/1.1 200 OK\r\n"
                        "Content-Type: application/json\r\n"
                        "Content-Length: " + QByteArray::number(data.size()) + "\r\n"
                        "\r\n";
        response.append(data);

        return response;
    });

    this->addGetRoute("/authViaToken", [this](Request& request) -> QByteArray {
        JWT::verifyTokenAndThrow(request, Env::get("SECRET"));

        std::shared_ptr<UserProvider> userProvider = this->getProvider<UserProvider>("userProvider");
        QByteArray data = userProvider->authUserViaToken(JWT::getUserIdFromToken(request.headers.get("authorization").toUtf8()));

        QByteArray response = "HTTP/1.1 200 OK\r\n"
                    "Content-Type: application/json\r\n"
                    "Content-Length: " + QByteArray::number(data.size()) + "\r\n"
                    "\r\n";
        response.append(data);

        return response;
    });

    this->addGetRoute("/refreshToken", [this](Request& request) -> QByteArray {
        JWT::verifyTokenAndThrow(request, Env::get("SECRET"));

        std::shared_ptr<UserProvider> userProvider = this->getProvider<UserProvider>("userProvider");
        QByteArray newToken = userProvider->refreshToken(request.headers.get("authorization").toUtf8());

        QByteArray response = "HTTP/1.1 200 Ok\r\n"
                    "Content-Type: application/json\r\n"
                    "Content-Length: " + QByteArray::number(newToken.size()) + "\r\n"
                    "\r\n";
        response.append(newToken);

        return response;
    });

    this->addPutRoute("/updateProfile", [this](Request& request) -> QByteArray {
        if(request.isBodyNoneJson == false || (request.headers.get("content-type") != "image/jpeg"
            && request.headers.get("Content-Type") != "image/png") || request.query.size() != 1
            || request.query.count("user_id") == 0 || Request::isInt(request.query["user_id"]) == false) {
            throw BadRequestException(
                "Invalid body format for update user profile",
                "Invalid body format for update user profile"
            );
        }

        std::shared_ptr<UserProvider> userProvider = this->getProvider<UserProvider>("userProvider");
        QByteArray data = userProvider->updateProfile(request.query["user_id"], request.bodyNoneJson);

        QByteArray response = "HTTP/1.1 200 OK\r\n"
                    "Content-Type: text/plain\r\n"
                    "Content-Length: " + QByteArray::number(data.size()) + "\r\n"
                    "\r\n";
        response.append(data);

        return response;
    });

    this->addPutRoute("/update", [this](Request& request) -> QByteArray {
        if(request.isBodyJsonObj == false || request.bodyJsonObj.size() != 4 || request.bodyJsonObj.contains("login") == false
            || request.bodyJsonObj.contains("email") == false || request.bodyJsonObj.contains("password") == false
            || request.bodyJsonObj.contains("id") == false) {
            throw BadRequestException(
                "Invalid body format for update user info",
                "Invalid body format for update user info"
            );
        }
        if (request.bodyJsonObj.value("id").isDouble() == false || request.bodyJsonObj.value("id").toInt() < 0
            || request.bodyJsonObj.value("login").isString() == false || request.bodyJsonObj.value("password").isString() == false
            || request.bodyJsonObj.value("email").isString() == false) {
            throw BadRequestException(
                "Invalid body format for update user info, unsupported types",
                "Invalid body format for update user info, unsupported types"
            );
        }

        std::shared_ptr<UserProvider> userProvider = this->getProvider<UserProvider>("userProvider");

        userProvider->updateBasicInfo(request.bodyJsonObj.value("id").toInt(),
                request.bodyJsonObj.value("login").toString(),
                request.bodyJsonObj.value("email").toString(),
                request.bodyJsonObj.value("password").toString());

        QByteArray response = "HTTP/1.1 200 OK\r\n"
                    "Content-Type: text/plain\r\n"
                    "Content-Length: 33\r\n"
                    "\r\n"
                    "User data was successfuly changed";

        return response;
    });



    this->addPostRoute("/addFavMusic", [this](Request& request) -> QByteArray {
        if(request.isBodyJsonObj == false || request.bodyJsonObj.size() != 2 || request.bodyJsonObj.contains("user_id") == false
            || request.bodyJsonObj.contains("music_id") == false || request.bodyJsonObj.value("user_id").isDouble() == false
            || request.bodyJsonObj.value("music_id").isDouble() == false || request.bodyJsonObj.value("user_id").toInt() < 0
            || request.bodyJsonObj.value("music_id").toInt() < 0) {
            throw BadRequestException(
                "Invalid body format for adding favorite music",
                "Invalid body format for adding favorite music"
            );
        }

        std::shared_ptr<UserProvider> userProvider = this->getProvider<UserProvider>("userProvider");

        userProvider->addFavoriteMusic(request.bodyJsonObj.value("music_id").toInt(),
                request.bodyJsonObj.value("user_id").toInt());

        QByteArray response = "HTTP/1.1 200 OK\r\n"
                        "Content-Type: text/plain\r\n"
                        "Content-Length: 27\r\n"
                        "\r\n"
                        "Music was added to favorite";

        return response;
    });

    this->addGetRoute("/getFavMusic", [this](Request& request) -> QByteArray {
        if(request.query.size() != 1 || request.query.count("user_id") == 0 || Request::isInt(request.query["user_id"]) == false) {
            throw BadRequestException(
                "Invalid query format for getting favorite music",
                "Invalid query format for getting favorite music"
            );
        }

        std::shared_ptr<UserProvider> userProvider = this->getProvider<UserProvider>("userProvider");
        QByteArray data = QJsonDocument(userProvider->getFavoriteMusics(request.query["user_id"])).toJson();

        QByteArray response = "HTTP/1.1 200 OK\r\n"
                        "Content-Type: application/json\r\n"
                        "Content-Length: " + QByteArray::number(data.size()) + "\r\n"
                        "\r\n";
        response.append(data);

        return response;
    });

    this->addDeleteRoute("/delFavMusic", [this](Request& request) -> QByteArray {
        if(request.query.size() != 2 || request.query.count("user_id") == 0 || request.query.count("music_id") == 0
            || !Request::isInt(request.query["user_id"]) || !Request::isInt(request.query["music_id"])
            || request.query["user_id"].toInt() < 0 || request.query["music_id"].toInt() < 0) {
            throw BadRequestException(
                "Invalid query format for deleting favorite music",
                "Invalid query format for deleting favorite music"
            );
        }

        std::shared_ptr<UserProvider> userProvider = this->getProvider<UserProvider>("userProvider");

        userProvider->deleteFavoriteMusic(request.query["music_id"], request.query["user_id"]);

        QByteArray response = "HTTP/1.1 200 OK\r\n"
                        "Content-Type: text/plain\r\n"
                        "Content-Length: 31\r\n"
                        "\r\n"
                        "Music was deleted from favorite";

        return response;
    });




    this->addPostRoute("/addFavAuthor", [this](Request& request) -> QByteArray {
        if(request.isBodyJsonObj == false || request.bodyJsonObj.size() != 2 || request.bodyJsonObj.contains("user_id") == false
            || request.bodyJsonObj.contains("author_id") == false) {
            throw BadRequestException(
                "Invalid body format for adding favorite author",
                "Invalid body format for adding favorite author"
            );
        }
        if(request.bodyJsonObj.value("user_id").isDouble() == false || request.bodyJsonObj.value("author_id").isDouble() == false
            || request.bodyJsonObj.value("user_id").toInt() < 0 || request.bodyJsonObj.value("author_id").toInt() < 0) {
            throw BadRequestException(
                "Invalid body format for adding favorite author, unsupported types",
                "Invalid body format for adding favorite author, unsupported types"
            );
        }

        std::shared_ptr<UserProvider> userProvider = this->getProvider<UserProvider>("userProvider");

        userProvider->addFavoriteAuthor(request.bodyJsonObj.value("author_id").toInt(),
                request.bodyJsonObj.value("user_id").toInt());

        QByteArray response = "HTTP/1.1 200 OK\r\n"
                        "Content-Type: text/plain\r\n"
                        "Content-Length: 28\r\n"
                        "\r\n"
                        "Author was added to favorite";

        return response;
    });

    this->addGetRoute("/getFavAuthor", [this](Request& request) -> QByteArray {
        if(request.query.size() != 1 || request.query.count("user_id") == 0 || Request::isInt(request.query["user_id"]) == false) {
            throw BadRequestException(
                "Invalid query format for getting favorite author",
                "Invalid query format for getting favorite author"
            );
        }

        std::shared_ptr<UserProvider> userProvider = this->getProvider<UserProvider>("userProvider");
        QByteArray data = QJsonDocument(userProvider->getFavoriteAuthors(request.query["user_id"])).toJson();

        QByteArray response = "HTTP/1.1 200 OK\r\n"
                        "Content-Type: application/json\r\n"
                        "Content-Length: " + QByteArray::number(data.size()) + "\r\n"
                        "\r\n";
        response.append(data);

        return response;
    });

    this->addDeleteRoute("/delFavAuthor", [this](Request& request) -> QByteArray {
        if(request.query.size() != 2 || request.query.count("user_id") == 0 || request.query.count("author_id") == 0
            || !Request::isInt(request.query["user_id"]) || !Request::isInt(request.query["author_id"])
            || request.query["user_id"].toInt() < 0 || request.query["author_id"].toInt() < 0) {
            throw BadRequestException(
                "Invalid body format for deleting favorite author",
                "Invalid body format for deleting favorite author"
            );
        }

        std::shared_ptr<UserProvider> userProvider = this->getProvider<UserProvider>("userProvider");

        userProvider->deleteFavoriteAuthor(request.query["author_id"], request.query["user_id"]);

        QByteArray response = "HTTP/1.1 200 OK\r\n"
                        "Content-Type: text/plain\r\n"
                        "Content-Length: 32\r\n"
                        "\r\n"
                        "Author was deleted from favorite";

        return response;
    });
}

