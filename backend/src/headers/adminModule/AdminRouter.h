#ifndef ADMINROUTER_H
#define ADMINROUTER_H

#include "../concepts/Router.h"
#include "../concepts/Provider.h"
#include <map>
#include <memory>

class AdminRouter : public Router {
public:
    AdminRouter();
private:
    void setupProviders();
    void setupRoutes();
};

#endif // ADMINROUTER_H
