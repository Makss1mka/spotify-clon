#include "../headers/concepts/router.h"
#include "../headers/concepts/routerDispatcher.h"
#include "../headers/concepts/Request.h"
#include "../headers/adminModule/AdminRouter.h"
#include "../headers/adminModule/AdminProvider.h"
#include <QByteArray>
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
    this->addGetRoute("/getAllUserInfo", [](Request request, Router* thisRouter) -> QByteArray {
        std::shared_ptr<AdminProvider> adminProvider = std::dynamic_pointer_cast<AdminProvider>(thisRouter->getProvider("adminProvider"));
        QByteArray data = adminProvider->getAllUserInfo();

        QByteArray response = "HTTP/1.1 200 OK\r\n"
                              "Content-Type: text/plain\r\n"
                              "Content-Length: " + QByteArray::number(data.size()) + "\r\n"
                              "\r\n";
        response.append(data);
        return response;
    });
}
