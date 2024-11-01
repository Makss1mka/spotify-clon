#ifndef ADMINROUTER_H
#define ADMINROUTER_H

#include "../concepts/Router.h"

class AdminRouter : public Router {
public:
    AdminRouter();
private:
    void setupProviders() override;
    void setupRoutes() override;
};

#endif // ADMINROUTER_H
