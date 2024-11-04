#include "../headers/concepts/router.h"
#include "../headers/concepts/Request.h"
#include "../headers/musicModule/MusicProvider.h"
#include "../headers/musicModule/MusicRouter.h"
#include <QByteArray>
#include <QFile>
#include <QString>

MusicRouter::MusicRouter() : Router("music") {
    this->setupProviders();
    this->setupRoutes();
}

MusicRouter::setupProviders() {
    this->addProvider("musicProvider", std::make_shared<MusicProvider>());
}

MusicRouter::setupRoutes() {
    this->addGetRoute("/getById", [this](Request &request) -> QByteArray {
        if(request.query.count("id") == 0) {
            QByteArray response = "HTTP/1.1 400 Bad Request\r\n"
                            "Content-Type: text/plain\r\n"
                            "Content-Length: 37\r\n"
                            "\r\n"
                            "Invalid query format for getting music";
            return response;
        }

        std::shared_ptr<MusicProvider> musicProvider = this->getProvider<MusicProvider>("musicProvider");
        QByteArray data = musicProvider->getById(request.query["id"]);
        QByteArray response;

        if (data != "") {

        } else {

        }

    });

    this->addGetRoute("/getFile", [this](Request &request) -> QByteArray {
        if(request.query.count("path") == 0) {
            QByteArray response = "HTTP/1.1 400 Bad Request\r\n"
                            "Content-Type: text/plain\r\n"
                            "Content-Length: 37\r\n"
                            "\r\n"
                            "Invalid query format for getting music file";
            return response;
        }

        std::shared_ptr<MusicProvider> musicProvider = this->getProvider<MusicProvider>("musicProvider");
        QByteArray data = musicProvider->getFile(request.query["path"]);
        QByteArray response;

        if (data != "") {
            response = "HTTP/1.1 200 OK\r\n"
                            "Content-Type: audio/mpeg\r\n"
                            "Content-Length: " + QByteArray::number(fileContent.size()) + "\r\n"
                            "\r\n";
            response.append(fileContent);
        } else {
            response = "HTTP/1.1 404 Not Found\r\n"
                            "Content-Type: text/plain\r\n"
                            "Content-Length: 20\r\n"
                            "\r\n"
                            "Music file not found\r\n";
        }
        return response;
    });
}
