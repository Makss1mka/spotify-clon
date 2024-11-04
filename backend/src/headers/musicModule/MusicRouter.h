#ifndef MUSICROUTER_H
#define MUSICROUTER_H

#include "../concepts/Router.h"

class MusicRouter : public Router {
public:
    MusicRouter();
private:
    void setupProviders() override;
    void setupRoutes() override;
};

#endif // MUSICROUTER_H
