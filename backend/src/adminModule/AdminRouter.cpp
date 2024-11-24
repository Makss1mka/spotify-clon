#include "../headers/concepts/router.h"
#include "../headers/concepts/Request.h"
#include "../headers/adminModule/AdminRouter.h"
#include "../headers/adminModule/AdminProvider.h"
#include "../headers/musicModule/MusicProvider.h"
#include "../headers/utils/exceptions.h"
#include "../headers/utils/statusCodes.h"
#include <QByteArray>
#include <QFile>

AdminRouter::AdminRouter() : Router("/admin") {
    this->setupRoutes();
    this->setupProviders();
}

void AdminRouter::setupProviders() {
    this->addProvider("adminProvider", std::make_shared<AdminProvider>());
    this->addProvider("musicProvider", std::make_shared<MusicProvider>());
}

void AdminRouter::setupRoutes() {
    this->addGetRoute("/getAllUserInfo", [this](Request& request) -> QByteArray {
        std::shared_ptr<AdminProvider> adminProvider = this->getProvider<AdminProvider>("adminProvider");
        QByteArray data = adminProvider->getAllUserInfo();
        QByteArray response;

        response = "HTTP/1.1 200 OK\r\n"
                    "Content-Type: application/json\r\n"
                    "Content-Length: " + QByteArray::number(data.size()) + "\r\n"
                    "\r\n";
        response.append(data);

        return response;
    });

    this->addGetRoute("/getBilly", [this](Request& request) -> QByteArray {
        QFile file(":/static/billy.jpg");
        if(file.open(QIODevice::ReadOnly)) {
            QByteArray fileContent = file.readAll();
            file.close();

            QByteArray response = "HTTP/1.1 200 OK\r\n"
                            "Content-Type: image/jpeg\r\n"
                            "Content-Length: " + QByteArray::number(fileContent.size()) + "\r\n"
                            "\r\n";
            response.append(fileContent);
            return response;
        } else {
            throw FileException(
                "Cannot find billy",
                "Cannot find billy",
                StatusCode::NOT_FOUND
            );
        }
    });

    this->addGetRoute("/getAllMusicInfo", [this](Request& request) -> QByteArray {
        std::shared_ptr<MusicProvider> musicProvider = this->getProvider<MusicProvider>("musicProvider");
        QByteArray data = musicProvider->getAll();
        QByteArray response;

        response = "HTTP/1.1 200 OK\r\n"
                   "Content-Type: application/json\r\n"
                   "Content-Length: " + QByteArray::number(data.size()) + "\r\n"
                                                       "\r\n";
        response.append(data);

        return response;
    });

}
