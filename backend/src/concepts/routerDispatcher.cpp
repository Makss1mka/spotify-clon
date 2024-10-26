#include "../headers/concepts/RouterDispatcher.h"

RouterDispatcher::RouterDispatcher() {}

RouterDispatcher& RouterDispatcher::getDispatcher() {
    static RouterDispatcher dispatcher;
    return dispatcher;
}

void RouterDispatcher::addRouter(Router &router) {
    routers.push_back(router);
}

QByteArray RouterDispatcher::routing(QByteArray &request) {
    QByteArray response;

    for(auto &router : routers) {
        response = router.routing(request);
    }

    if(response.length() != 0) return response;

    response = "HTTP/1.1 404 Not Found\r\n"
          "Content-Type: text/plain\r\n"
          "Content-Length: 9\r\n"
          "\r\n"
          "Not Found";
    return response;
}


