#include "../headers/concepts/RouterDispatcher.h"
#include "../headers/concepts/Request.h"
#include "../headers/utils/exceptions.h"

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

    try {
        for(auto &router : routers) {
            response = router->routing(request);
            if (response != "") return response;
        }
        throw NotFoundException(
            "Not found",
            "Not found"
        );
    } catch (HandlingException& exc) {
        qDebug() << exc.getMessage();

        response = "HTTP/1.1 " + exc.getCode().toUtf8() + "\r\n"
                "Content-Type: text/plain\r\n"
                "Content-Length: " + QByteArray::number(exc.getResponseBodyData().size()) + "\r\n"
                "\r\n";
        response.append(exc.getResponseBodyData());
    }

    return response;
}


