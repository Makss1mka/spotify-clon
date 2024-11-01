#include "../headers/concepts/RouterDispatcher.h"
#include "../headers/concepts/Request.h"

RouterDispatcher::RouterDispatcher() {}

RouterDispatcher& RouterDispatcher::getDispatcher() {
    static RouterDispatcher dispatcher;
    return dispatcher;
}

void RouterDispatcher::addRouter(std::shared_ptr<Router> router) {
    routers.push_back(router);
}

QByteArray RouterDispatcher::routing(Request &request) {
    QByteArray response;

    for(auto &router : routers) {
        response = router->routing(request);
        if (response != "") return response;
    }

    response = "HTTP/1.1 404 Not Found\r\n"
          "Content-Type: text/plain\r\n"
          "Content-Length: 9\r\n"
          "\r\n"
          "Not Found";
    return response;
}


