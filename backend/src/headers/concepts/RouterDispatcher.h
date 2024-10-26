#ifndef ROUTERDISPATCHER_H
#define ROUTERDISPATCHER_H

#include <vector>
#include "Router.h"

class RouterDispatcher {
public:
    static RouterDispatcher& getDispatcher();

    RouterDispatcher(const RouterDispatcher&) = delete;
    void operator=(const RouterDispatcher&) = delete;

    QByteArray routing(QByteArray &request);
    void addRouter(Router &router);
private:
    RouterDispatcher();

    std::vector<Router> routers;
};

#endif // ROUTERDISPATCHER_H
