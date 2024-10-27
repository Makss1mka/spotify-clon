#ifndef ROUTER_H
#define ROUTER_H

#include <QDebug>
#include <vector>
#include <QByteArray>
#include <functional>
#include "Request.h"

class Router {
public:
    Router(std::string urlPrefix = "");

    QByteArray routing(Request &request);
    bool addGetRoute(std::string url, QByteArray (*handler) (Request));
    bool addPostRoute(std::string url, QByteArray (*handler) (Request));
    bool addUpdateRoute(std::string url, QByteArray (*handler) (Request));
    bool addDeleteRoute(std::string url, QByteArray (*handler) (Request));
    void getRouterInfo();
private:
    std::string urlPrefix;
    bool addRoute(std::string method, std::string url, QByteArray (*handler) (Request));

    class Route {
    public:
        Route(std::string method, std::string url, QByteArray (*handler) (Request));
        std::string url;
        std::string method;
        QByteArray (*handler) (Request);
    };

    std::vector<Route> routes;
};

#endif // ROUTER_H
