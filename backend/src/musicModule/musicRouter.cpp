#include "../headers/concepts/router.h"
#include "../headers/concepts/Request.h"
#include "../headers/musicModule/MusicProvider.h"
#include "../headers/musicModule/MusicRouter.h"
#include "../headers/utils/exceptions.h"
#include <QByteArray>
#include <QFile>
#include <QString>

MusicRouter::MusicRouter() : Router("/music") {
    this->setupProviders();
    this->setupRoutes();
}

void MusicRouter::setupProviders() {
    this->addProvider("musicProvider", std::make_shared<MusicProvider>());
}

void MusicRouter::setupRoutes() {
    this->addGetRoute("/getById", [this](Request &request) -> QByteArray {
        qDebug() << "JOPA";
        if(request.query.count("id") == 0) {
            throw BadRequestException(
                "Invalid query format for getting music",
                "Invalid query format for getting music"
            );
        }

        std::shared_ptr<MusicProvider> musicProvider = this->getProvider<MusicProvider>("musicProvider");
        QByteArray data = musicProvider->getById(request.query["id"]);
        QByteArray response = "HTTP/1.1 200 OK\r\n"
                        "Content-Type: application/json\r\n"
                        "Content-Length: " + QByteArray::number(data.size()) + "\r\n"
                        "\r\n";
        response.append(data);

        return response;
    });

    this->addGetRoute("/getFile", [this](Request &request) -> QByteArray {
        if(request.query.count("path") == 0) {
            throw BadRequestException(
                "Invalid query format for getting music file",
                "Invalid query format for getting music file"
            );
        }

        std::shared_ptr<MusicProvider> musicProvider = this->getProvider<MusicProvider>("musicProvider");
        QByteArray data = musicProvider->getFile(request.query["path"]);

        QByteArray response = "HTTP/1.1 200 OK\r\n"
                        "Content-Type: audio/mpeg\r\n"
                        "Content-Length: " + QByteArray::number(data.size()) + "\r\n"
                        "\r\n";
        response.append(data);

        return response;
    });

    this->addGetRoute("/getByAuthor", [this](Request& request) -> QByteArray {
        if(request.query.count("author_name") == 0) {
            throw BadRequestException(
                "Invalid query format for getting musics by author",
                "Invalid query format for getting musics by author"
            );
        }

        std::shared_ptr<MusicProvider> musicProvider = this->getProvider<MusicProvider>("musicProvider");
        QByteArray data = musicProvider->getByAuthor(request.query["author_name"]);

        QByteArray response = "HTTP/1.1 200 OK\r\n"
                        "Content-Type: application/json\r\n"
                        "Content-Length: " + QByteArray::number(data.size()) + "\r\n"
                        "\r\n";
        response.append(data);

        return response;
    });

    this->addGetRoute("/findByName", [this](Request& request) -> QByteArray {
        if(request.query.count("key") == 0) {
            throw BadRequestException(
                "Invalid query format for finding musics",
                "Invalid query format for finding musics"
            );
        }

        std::shared_ptr<MusicProvider> musicProvider = this->getProvider<MusicProvider>("musicProvider");
        QByteArray data = musicProvider->findByName(request.query["key"]);

        QByteArray response = "HTTP/1.1 200 OK\r\n"
                        "Content-Type: application/json\r\n"
                              "Content-Length: " + QByteArray::number(data.size()) + "\r\n"
                        "\r\n";
        response.append(data);

        return response;
    });
}

