#include "../headers/concepts/router.h"
#include "../headers/concepts/Request.h"
#include "../headers/adminModule/AdminRouter.h"
#include "../headers/adminModule/AdminProvider.h"
#include <QByteArray>
#include <QFile>

AdminRouter::AdminRouter() : Router("/admin") {
    this->setupRoutes();
    this->setupProviders();
}

void AdminRouter::setupProviders() {
    std::shared_ptr<AdminProvider> adminProvider = std::make_shared<AdminProvider>();

    this->addProvider("adminProvider", adminProvider);
}

void AdminRouter::setupRoutes() {
    this->addGetRoute("/getAllUserInfo", [this](Request& request) -> QByteArray {
        qDebug() << "Jopa";
        std::shared_ptr<AdminProvider> adminProvider = std::dynamic_pointer_cast<AdminProvider>(this->getProvider("adminProvider"));
        qDebug() << "Jopa 2";
        QByteArray data = adminProvider->getAllUserInfo();
        QByteArray response;

        if(data == "") {
            response = "HTTP/1.1 503 Service Unavailable\r\n"
                        "Content-Type: text/plain\r\n"
                        "Content-Length: 39\r\n"
                        "\r\n"
                        "Admin service is temporarily unavailable";
        } else {
            response = "HTTP/1.1 200 OK\r\n"
                        "Content-Type: application/json\r\n"
                        "Content-Length: " + QByteArray::number(data.size()) + "\r\n"
                        "\r\n";
            response.append(data);
        }
        return response;
    });

    this->addGetRoute("/getBilly", [this](Request& request) -> QByteArray {
        qDebug() << "POPA 2";
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
        }
        return "";
    });

}
