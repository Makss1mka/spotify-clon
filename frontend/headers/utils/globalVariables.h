#ifndef GLOBALVARIABLES_H
#define GLOBALVARIABLES_H

#include "./HttpClient.h"
#include "./Player.h"

namespace Globals {
    extern Player* player;
    extern std::shared_ptr<HttpClient> httpClient;
}

#endif // GLOBALVARIABLES_H
