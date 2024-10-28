#include "../headers/concepts/router.h"
#include "../headers/concepts/routerDispatcher.h"
#include "../headers/concepts/Request.h"
#include "../headers/adminModule/AdminRouter.h"
#include "../headers/adminModule/AdminProvider.h"
#include <QByteArray>
#include<QFile>
#include <iostream>
#include <memory>
#include <functional>

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
        std::shared_ptr<AdminProvider> adminProvider = std::dynamic_pointer_cast<AdminProvider>(this->getProvider("adminProvider"));
        QByteArray data = adminProvider->getAllUserInfo();

        QByteArray response = "HTTP/1.1 200 OK\r\n"
                              "Content-Type: text/plain\r\n"
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
        }
        return "";
    });

}
