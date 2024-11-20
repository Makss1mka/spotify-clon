#ifndef GLOBALVARIABLES_H
#define GLOBALVARIABLES_H

#include "./HttpClient.h"
#include "./Player.h"
#include "../app.h"

namespace Globals {
    extern Player* player;
    extern HttpClient* httpClient;
}

#endif // GLOBALVARIABLES_H
