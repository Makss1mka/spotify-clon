#ifndef ROUTER_H
#define ROUTER_H

#include <QDebug>
#include <vector>
#include <QByteArray>
#include <functional>

class Router {
public:
    Router(std::string urlPrefix = "");

    QByteArray routing(QByteArray &request);
    bool addGetRoute(std::string url, QByteArray (*handler) (QByteArray));
    bool addPostRoute(std::string url, QByteArray (*handler) (QByteArray));
    bool addUpdateRoute(std::string url, QByteArray (*handler) (QByteArray));
    bool addDeleteRoute(std::string url, QByteArray (*handler) (QByteArray));
private:
    std::string urlPrefix;
    bool addRoute(std::string method, std::string url, QByteArray (*handler) (QByteArray));

    class Route {
    public:
        Route(std::string method, std::string url, QByteArray (*handler) (QByteArray)) {
            method = method;
            url = url;
            handler = handler;
        }
        std::string url;
        std::string method;
        QByteArray (*handler) (QByteArray);
    };

    std::vector<Route> routes;
};

#endif // ROUTER_H
