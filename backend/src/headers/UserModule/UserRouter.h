#ifndef USERHANDLERS_H
#define USERHANDLERS_H

#include "../concepts/Router.h"

class UserRouter : public Router {
public:
    UserRouter();
private:
    void setupProviders() override;
    void setupRoutes() override;
};

#endif // USERHANDLERS_H
