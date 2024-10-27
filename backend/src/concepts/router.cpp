#include "../headers/concepts/Router.h"
#include "../headers/concepts/Request.h"

Router::Router(std::string urlPrefix) {
    this->urlPrefix = urlPrefix;
}

Router::Route::Route(std::string method, std::string url, QByteArray (*handler) (Request&, Router*)) {
    this->method = method;
    this->handler = handler;
    this->url = url;
}

bool Router::addRoute(std::string method, std::string url, QByteArray (*handler) (Request&, Router*)) {
    for(auto &route : routes) {
        if(url == route.url && method == route.method) return false;
    }

    routes.push_back(Route(method, url, handler));
    return true;
}

bool Router::addGetRoute(std::string url, QByteArray (*handler) (Request&, Router*)) {
    return addRoute("GET", url, handler);
}

bool Router::addPostRoute(std::string url, QByteArray (*handler) (Request&, Router*)) {
    return addRoute("POST", url, handler);
}

bool Router::addUpdateRoute(std::string url, QByteArray (*handler) (Request&, Router*)) {
    return addRoute("UPDATE", url, handler);
}

bool Router::addDeleteRoute(std::string url, QByteArray (*handler) (Request&, Router*)) {
    return addRoute("DELETE", url, handler);
}

QByteArray Router::routing(Request &request) {
    for(auto& route : routes) {
        if(request.url == urlPrefix + route.url && request.method == route.method) {
            return route.handler(request, this);
        }
    }
    QByteArray response = "";
    return response;
}

void Router::getRouterInfo() {
    qDebug() << urlPrefix;
    for(auto& route : routes) {
        qDebug() << route.method << " " << route.url;
    }
}

void Router::addProvider(const std::string& key, std::shared_ptr<Provider> provider) {
    providers[key] = provider;
}

std::shared_ptr<Provider> Router::getProvider(const std::string& key) {
    return providers[key];
}
