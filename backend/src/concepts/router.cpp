#include "../headers/concepts/Router.h"

Router::Router(std::string urlPrefix) {
    urlPrefix = urlPrefix;
}

bool Router::addRoute(std::string method, std::string url, QByteArray (*handler)(QByteArray)) {
    for(auto &route : routes) {
        if(url == route.url && method == route.method) return false;
    }

    routes.push_back(Route(method, url, handler));
    return true;
}

bool Router::addGetRoute(std::string url, QByteArray (*handler) (QByteArray)) {
    return addRoute("GET ", url, handler);
}

bool Router::addPostRoute(std::string url, QByteArray (*handler) (QByteArray)) {
    return addRoute("POST ", url, handler);
}

bool Router::addUpdateRoute(std::string url, QByteArray (*handler) (QByteArray)) {
    return addRoute("UPDATE ", url, handler);
}

bool Router::addDeleteRoute(std::string url, QByteArray (*handler) (QByteArray)) {
    return addRoute("DELETE ", url, handler);
}

QByteArray Router::routing(QByteArray &request) {
    for(auto& route : routes) {
        if(request.contains(route.method + urlPrefix + route.url)) {
            return route.handler(request);
        }
    }
    QByteArray response = "";
    return response;
}
