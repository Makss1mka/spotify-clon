#include "../headers/concepts/Router.h"
#include "../headers/concepts/Request.h"
#include <functional>

Router::Router(std::string urlPrefix) {
    this->urlPrefix = urlPrefix;
}

Router::Route::Route(std::string method, std::string url, std::function<QByteArray(Request&)> handler) {
    this->method = method;
    this->handler = handler;
    this->url = url;
}

bool Router::addRoute(std::string method, std::string url, std::function<QByteArray(Request&)> handler) {
    for(auto &route : routes) {
        if(url == route.url && method == route.method) return false;
    }

    routes.push_back(Route(method, url, handler));
    return true;
}

bool Router::addGetRoute(std::string url, std::function<QByteArray(Request&)> handler) {
    return addRoute("GET", url, handler);
}

bool Router::addPostRoute(std::string url, std::function<QByteArray(Request&)> handler) {
    return addRoute("POST", url, handler);
}

bool Router::addPutRoute(std::string url, std::function<QByteArray(Request&)> handler) {
    return addRoute("PUT", url, handler);
}

bool Router::addDeleteRoute(std::string url, std::function<QByteArray(Request&)> handler) {
    return addRoute("DELETE", url, handler);
}

QByteArray Router::routing(Request &request) {
    for(auto& route : routes) {
        if(request.url == urlPrefix + route.url && request.method == route.method) {
            return route.handler(request);
        }
    }
    return "";
}

void Router::getRouterInfo() {
    qDebug() << urlPrefix;
    for(auto& route : routes) {
        qDebug() << route.method << " " << route.url;
    }
    for(auto& [key, provider] : providers) {
        qDebug() << key;
    }
}

void Router::addProvider(const std::string& key, std::shared_ptr<Provider> provider) {
    providers.set(key, provider);
}

