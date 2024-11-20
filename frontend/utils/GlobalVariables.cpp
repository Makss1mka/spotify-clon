#include "../headers/utils/globalVariables.h"
#include "../headers/utils/HttpClient.h"
#include "./headers/app.h"
#include <QMediaPlayer>

namespace Globals {
    HttpClient* httpClient = new HttpClient();
    Player* player = new Player();
}
