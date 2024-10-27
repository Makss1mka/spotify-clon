#include "../headers/concepts/router.h"
#include "../headers/concepts/routerDispatcher.h"
#include "../headers/concepts/Request.h"
#include "../concepts/router.cpp"
#include <QByteArray>
#include <iostream>

Router adminRouter() {
    Router adminRouter = Router("/admin");

    adminRouter.addGetRoute("/getAllUserInfo", [](Request request) -> QByteArray {
        QByteArray response = "HTTP/1.1 200 OK\r\n"
                    "Content-Type: text/plain\r\n"
                    "Content-Length: 5\r\n"
                    "\r\n"
                    "hello";
        return response;
    });


    return adminRouter;
}
