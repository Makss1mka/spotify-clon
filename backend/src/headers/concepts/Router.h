#ifndef ROUTER_H
#define ROUTER_H

#include <QDebug>
#include <vector>
#include <QByteArray>
#include <functional>
#include "Request.h"
#include "Provider.h"

class Router {
public:
    Router(std::string urlPrefix = "");

    QByteArray routing(Request &request);
    bool addGetRoute(std::string url, QByteArray (*handler) (Request&, Router*));
    bool addPostRoute(std::string url, QByteArray (*handler) (Request&, Router*));
    bool addUpdateRoute(std::string url, QByteArray (*handler) (Request&, Router*));
    bool addDeleteRoute(std::string url, QByteArray (*handler) (Request&, Router*));
    void getRouterInfo();

    void addProvider(const std::string& key, std::shared_ptr<Provider>provider);
    std::shared_ptr<Provider> getProvider(const std::string& key);
private:
    std::string urlPrefix;
    bool addRoute(std::string method, std::string url, QByteArray (*handler) (Request&, Router*));

    class Route {
    public:
        Route(std::string method, std::string url, QByteArray (*handler) (Request&, Router*));
        std::string url;
        std::string method;
        QByteArray (*handler) (Request);
    };

    std::vector<Route> routes;
    std::map<std::string, std::shared_ptr<Provider>> providers;
};

#endif // ROUTER_H
