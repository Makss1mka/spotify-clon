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

    virtual void setupProviders() = 0;
    virtual void setupRoutes() = 0;

    QByteArray routing(Request &request);
    bool addGetRoute(std::string url, std::function<QByteArray(Request&)> handler);
    bool addPostRoute(std::string url, std::function<QByteArray(Request&)> handler);
    bool addUpdateRoute(std::string url, std::function<QByteArray(Request&)> handler);
    bool addDeleteRoute(std::string url, std::function<QByteArray(Request&)> handler);
    void getRouterInfo();

    void addProvider(const std::string& key, std::shared_ptr<Provider> provider);

    template<typename T>
    std::shared_ptr<T> getProvider(const std::string& key) {
        return std::dynamic_pointer_cast<T>(this->providers[key]);
    }
protected:
    std::string urlPrefix;
    bool addRoute(std::string method, std::string url, std::function<QByteArray(Request&)> handler);

    class Route {
    public:
        Route(std::string method, std::string url, std::function<QByteArray(Request&)> handler);
        std::string url;
        std::string method;
        std::function<QByteArray(Request&)> handler;
    };

    std::vector<Route> routes;
    std::map<std::string, std::shared_ptr<Provider>> providers;
};

#endif // ROUTER_H
