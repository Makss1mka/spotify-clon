#include "../headers/concepts/router.h"
#include "../headers/concepts/Request.h"
#include "../headers/musicModule/MusicProvider.h"
#include "../headers/musicModule/MusicRouter.h"
#include "../headers/utils/exceptions.h"
#include "../headers/utils/envFile.h"
#include <QByteArray>
#include <QFile>
#include <QString>
#include <functional>

MusicRouter::MusicRouter() : Router("/music") {
    this->setupProviders();
    this->setupRoutes();
}

void MusicRouter::setupProviders() {
    this->addProvider("musicProvider", std::make_shared<MusicProvider>());
}

void MusicRouter::setupRoutes() {
    this->addGetRoute("/getById", [this](Request &request) -> QByteArray {
        if(request.query.size() != 1 || request.query.count("id") == 0 || Request::isInt(request.query["id"]) == false) {
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

    this->addGetRoute("/getAudio", [this](Request &request) -> QByteArray {
        if(request.query.size() != 1 || request.query.count("path") == 0) {
            throw BadRequestException(
                "Invalid query format for getting music file",
                "Invalid query format for getting music file"
            );
        }

        std::shared_ptr<MusicProvider> musicProvider = this->getProvider<MusicProvider>("musicProvider");
        QByteArray data = musicProvider->getFile(Env::get("MUSIC_DIR") + request.query["path"]);

        QByteArray response = "HTTP/1.1 200 OK\r\n"
                        "Content-Type: audio/mpeg\r\n"
                        "Content-Length: " + QByteArray::number(data.size()) + "\r\n"
                        "\r\n";
        response.append(data);

        return response;
    });

    this->addGetRoute("/getProfile", [this](Request &request) -> QByteArray {
        if(request.query.size() != 1 || request.query.count("path") == 0) {
            throw BadRequestException(
                "Invalid query format for getting profile picture",
                "Invalid query format for getting profile picture"
            );
        }

        QByteArray pictureType;
        if(request.query["path"].split(".")[1] == "jpg") {
            pictureType = "image/jpeg";
        } else if (request.query["path"].split(".")[1] == "png") {
            pictureType = "image/png";
        } else {
            throw BadRequestException(
                "Invalid file format for getting profile picture",
                "Invalid file format for getting profile picture"
            );
        }

        std::shared_ptr<MusicProvider> musicProvider = this->getProvider<MusicProvider>("musicProvider");
        QByteArray data = musicProvider->getFile(Env::get("PROFILES_DIR") + request.query["path"]);

        QByteArray response = "HTTP/1.1 200 OK\r\n"
                        "Content-Type: " + pictureType + "\r\n"
                        "Content-Length: " + QByteArray::number(data.size()) + "\r\n"
                        "\r\n";
        response.append(data);

        return response;
    });

    this->addGetRoute("/getByAuthor", [this](Request& request) -> QByteArray {
        if(request.query.size() != 1 || request.query.count("author_name") == 0) {
            throw BadRequestException(
                "Invalid query format for getting musics by author",
                "Invalid query format for getting musics by author"
            );
        }

        std::shared_ptr<MusicProvider> musicProvider = this->getProvider<MusicProvider>("musicProvider");
        QByteArray data = musicProvider->getByAuthor(request.query["author_name"].replace("%20", " "));

        QByteArray response = "HTTP/1.1 200 OK\r\n"
                        "Content-Type: application/json\r\n"
                        "Content-Length: " + QByteArray::number(data.size()) + "\r\n"
                        "\r\n";
        response.append(data);

        return response;
    });

    this->addGetRoute("/findByName", [this](Request& request) -> QByteArray {
        if(request.query.size() != 1 || request.query.count("key") == 0) {
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



    this->addGetRoute("/recomend", [this](Request& request) -> QByteArray {
        if(request.query.size() != 5 || request.query.count("janre") == 0 || request.query.count("author") == 0
            || request.query.count("lang") == 0 || request.query.count("track_name") == 0
            || request.query.count("limit") == 0 || Request::isInt(request.query["limit"]) == false) {
            throw BadRequestException(
                "Invalid query format for recommend musics",
                "Invalid query format for recommend musics"
            );
        }

        std::shared_ptr<MusicProvider> musicProvider = this->getProvider<MusicProvider>("musicProvider");
        QByteArray data = musicProvider->recomend(request.query["limit"].toInt(),
                request.query["janre"].replace("%20", " "),
                request.query["author"].replace("%20", " "),
                request.query["lang"].replace("%20", " "),
                request.query["track_name"].replace("%20", " "));

        QByteArray response = "HTTP/1.1 200 OK\r\n"
                        "Content-Type: application/json\r\n"
                        "Content-Length: " + QByteArray::number(data.size()) + "\r\n"
                        "\r\n";
        response.append(data);

        return response;
    });

    this->addGetRoute("/find", [this](Request& request) -> QByteArray {
        if(request.query.size() != 1 || request.query.count("key") == 0) {
            throw BadRequestException(
                "Invalid query format for finding",
                "Invalid query format for finding"
            );
        }

        std::shared_ptr<MusicProvider> musicProvider = this->getProvider<MusicProvider>("musicProvider");
        QByteArray data = musicProvider->find(request.query["key"].replace("%20", " "));

        QByteArray response = "HTTP/1.1 200 OK\r\n"
                "Content-Type: application/json\r\n"
                "Content-Length: " + QByteArray::number(data.size()) + "\r\n"
                "\r\n";
        response.append(data);

        return response;
    });



    this->addPostRoute("/addMusicBasicInfo", [this](Request& request) -> QByteArray {
        if(request.isBodyJsonObj == false  || request.bodyJsonObj.size() != 4
            || request.bodyJsonObj.contains("name") == 0 || request.bodyJsonObj.contains("lang") == 0
            || request.bodyJsonObj.contains("janres") == 0 || request.bodyJsonObj.contains("author_id") == 0) {
            throw BadRequestException(
                "Invalid body format for adding music",
                "Invalid body format for adding music"
            );
        }

        if (request.bodyJsonObj.value("name").isString() == false || request.bodyJsonObj.value("lang").isString() == false
            || request.bodyJsonObj.value("janres").isString() == false || request.bodyJsonObj.value("author_id").isDouble() == false
            || request.bodyJsonObj.value("author_id").toInt() < 0) {
            throw BadRequestException(
                "Invalid body format for adding music, unsupported types",
                "Invalid body format for adding music, unsupported types"
            );
        }

        std::shared_ptr<MusicProvider> musicProvider = this->getProvider<MusicProvider>("musicProvider");
        QByteArray data = musicProvider->addMusicBasicInfo(request.bodyJsonObj.value("author_id").toInt(),
                request.bodyJsonObj.value("name").toString(),
                request.bodyJsonObj.value("lang").toString(),
                request.bodyJsonObj.value("janres").toString());

        QByteArray response = "HTTP/1.1 201 Created\r\n"
                "Content-Type: application/json\r\n"
                "Content-Length: " + QByteArray::number(data.size()) + "\r\n"
                "\r\n";
        response.append(data);

        return response;
    });

    this->addPostRoute("/addMusicFile", [this](Request& request) -> QByteArray {
        if(request.isBodyNoneJson == false || request.headers.get("content-type") != "audio/mpeg"
            || request.query.size() != 1 || request.query.count("music_id") == 0
            || Request::isInt(request.query["music_id"]) == false || request.query["music_id"].toInt() < 0) {
            throw BadRequestException(
                "Invalid body format for adding music audio file",
                "Invalid body format for adding music audio file"
            );
        }

        std::shared_ptr<MusicProvider> musicProvider = this->getProvider<MusicProvider>("musicProvider");
        musicProvider->addMusicFile(request.query["music_id"].toInt(), request.bodyNoneJson);

        QByteArray response = "HTTP/1.1 201 Created\r\n"
                "Content-Type: text/plain\r\n"
                "Content-Length: 20\r\n"
                "\r\n"
                "Audio file was added";

        return response;
    });

    this->addPostRoute("/addMusicProfile", [this](Request& request) -> QByteArray {
        if(request.isBodyNoneJson == false || (request.headers.get("content-type") != "image/jpeg"
            && request.headers.get("content-type") != "image/png" && request.headers.get("content-type") != "image/jpg")
            || request.query.size() != 1 || request.query.count("music_id") == 0
            || Request::isInt(request.query["music_id"]) == false || request.query["music_id"].toInt() < 0) {
            throw BadRequestException(
                "Invalid body format for adding music profile",
                "Invalid body format for adding music profile"
            );
        }

        std::shared_ptr<MusicProvider> musicProvider = this->getProvider<MusicProvider>("musicProvider");
        musicProvider->addMusicProfile(request.query["music_id"].toInt(),
                request.headers.get("content-type").split('/')[1],
                request.bodyNoneJson);

        QByteArray response = "HTTP/1.1 200 OK\r\n"
                "Content-Type: text/plain\r\n"
                "Content-Length: 25\r\n"
                "\r\n"
                "Profile was added/updated";

        return response;
    });

    this->addPutRoute("/updateMusicBasicInfo", [this](Request& request) -> QByteArray {
        if(request.isBodyJsonObj == false || request.bodyJsonObj.size() != 4
            || request.bodyJsonObj.contains("name") == 0 || request.bodyJsonObj.contains("lang") == 0
            || request.bodyJsonObj.contains("janres") == 0 || request.bodyJsonObj.contains("music_id") == 0) {
            throw BadRequestException(
                "Invalid body format for adding music",
                "Invalid body format for adding music"
            );
        }

        if (request.bodyJsonObj.value("name").isString() == false || request.bodyJsonObj.value("lang").isString() == false
            || request.bodyJsonObj.value("janres").isString() == false || request.bodyJsonObj.value("music_id").isDouble() == false
            || request.bodyJsonObj.value("music_id").toInt() < 0) {
            throw BadRequestException(
                "Invalid body format for adding music, unsupported types",
                "Invalid body format for adding music, unsupported types"
            );
        }

        std::shared_ptr<MusicProvider> musicProvider = this->getProvider<MusicProvider>("musicProvider");
        musicProvider->addMusicBasicInfo(request.bodyJsonObj.value("music_id").toInt(),
                request.bodyJsonObj.value("name").toString(),
                request.bodyJsonObj.value("lang").toString(),
                request.bodyJsonObj.value("janres").toString());

        QByteArray response = "HTTP/1.1 200 OK\r\n"
                "Content-Type: text/plain\r\n"
                "Content-Length: 22\r\n"
                "\r\n"
                "Music data was updated";

        return response;
    });

}

