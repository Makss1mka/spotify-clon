#ifndef USERHANDLERS_H
#define USERHANDLERS_H

#include "../concepts/Router.h"

class AuthRouter : public Router {
public:
    AuthRouter();
private:
    void setupProviders() override;
    void setupRoutes() override;
};

#endif // USERHANDLERS_H
