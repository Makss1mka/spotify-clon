#ifndef ROUTERDISPATCHER_H
#define ROUTERDISPATCHER_H

#include <vector>
#include "Router.h"
#include "Request.h"

class RouterDispatcher {
public:
    static RouterDispatcher& getDispatcher();

    RouterDispatcher(const RouterDispatcher&) = delete;
    void operator=(const RouterDispatcher&) = delete;

    QByteArray routing(Request &request);
    void addRouter(Router router);
private:
    RouterDispatcher();

    std::vector<Router> routers;
};

#endif // ROUTERDISPATCHER_H
