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



    this->addPostRoute("/addFavMusic", [this](Request& request) -> QByteArray {
        if(request.body.size() != 2 || request.body.count("user_id") == 0 || request.body.count("music_id") == 0) {
            throw BadRequestException(
                "Invalid body format for adding favorite music",
                "Invalid body format for adding favorite music"
            );
        }

        std::shared_ptr<UserProvider> userProvider = this->getProvider<UserProvider>("userProvider");

        userProvider->addFavoriteMusic(request.body["music_id"], request.body["user_id"]);

        QByteArray response = "HTTP/1.1 200 OK\r\n"
                        "Content-Type: text/plain\r\n"
                        "Content-Length: 33\r\n"
                        "\r\n"
                        "Music wa added to favorite";

        return response;
    });

    this->addGetRoute("/getFavMusic", [this](Request& request) -> QByteArray {
        if(request.query.size() != 1 || request.query.count("user_id") == 0) {
            throw BadRequestException(
                "Invalid query format for getting favorite music",
                "Invalid query format for getting favorite music"
            );
        }

        std::shared_ptr<UserProvider> userProvider = this->getProvider<UserProvider>("userProvider");
        QByteArray data = userProvider->getFavoriteMusics(request.query["user_id"]);

        QByteArray response = "HTTP/1.1 200 OK\r\n"
                        "Content-Type: application/json\r\n"
                        "Content-Length: " + QByteArray::number(data.size()) + "\r\n"
                        "\r\n";
        response.append(data);

        return response;
    });

    this->addDeleteRoute("/delFavMusic", [this](Request& request) -> QByteArray {
        if(request.body.size() != 2 || request.body.count("user_id") == 0 || request.body.count("music_id") == 0) {
            throw BadRequestException(
                "Invalid body format for deleting favorite music",
                "Invalid body format for deleting favorite music"
            );
        }

        std::shared_ptr<UserProvider> userProvider = this->getProvider<UserProvider>("userProvider");

        userProvider->deleteFavoriteMusic(request.body["music_id"], request.body["user_id"]);

        QByteArray response = "HTTP/1.1 200 OK\r\n"
                        "Content-Type: text/plain\r\n"
                        "Content-Length: 33\r\n"
                        "\r\n"
                        "Music was deleted from favorite";

        return response;
    });




    this->addPostRoute("/addFavAuthor", [this](Request& request) -> QByteArray {
        if(request.body.size() != 2 || request.body.count("user_id") == 0 || request.body.count("author_id") == 0) {
            throw BadRequestException(
                "Invalid body format for adding favorite author",
                "Invalid body format for adding favorite author"
            );
        }

        std::shared_ptr<UserProvider> userProvider = this->getProvider<UserProvider>("userProvider");

        userProvider->addFavoriteAuthor(request.body["author_id"], request.body["user_id"]);

        QByteArray response = "HTTP/1.1 200 OK\r\n"
                        "Content-Type: text/plain\r\n"
                        "Content-Length: 33\r\n"
                        "\r\n"
                        "Author wa added to favorite";

        return response;
    });

    this->addGetRoute("/getFavAuthor", [this](Request& request) -> QByteArray {
        if(request.query.size() != 1 || request.query.count("user_id") == 0) {
            throw BadRequestException(
                "Invalid query format for getting favorite author",
                "Invalid query format for getting favorite author"
            );
        }

        std::shared_ptr<UserProvider> userProvider = this->getProvider<UserProvider>("userProvider");
        QByteArray data = userProvider->getFavoriteAuthors(request.query["user_id"]);

        QByteArray response = "HTTP/1.1 200 OK\r\n"
                        "Content-Type: application/json\r\n"
                        "Content-Length: " + QByteArray::number(data.size()) + "\r\n"
                        "\r\n";
        response.append(data);

        return response;
    });

    this->addDeleteRoute("/delFavAuthor", [this](Request& request) -> QByteArray {
        if(request.body.size() != 2 || request.body.count("user_id") == 0 || request.body.count("author_id") == 0) {
            throw BadRequestException(
                "Invalid body format for deleting favorite author",
                "Invalid body format for deleting favorite author"
            );
        }

        std::shared_ptr<UserProvider> userProvider = this->getProvider<UserProvider>("userProvider");

        userProvider->deleteFavoriteAuthor(request.body["author_id"], request.body["user_id"]);

        QByteArray response = "HTTP/1.1 200 OK\r\n"
                        "Content-Type: text/plain\r\n"
                        "Content-Length: 33\r\n"
                        "\r\n"
                        "Author was deleted from favorite";

        return response;
    });
}

