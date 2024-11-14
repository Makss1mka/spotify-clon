#include "../headers/utils/globalVariables.h"
#include "../headers/utils/HttpClient.h"
#include "./headers/app.h"
#include <QMediaPlayer>

namespace Globals {
    std::shared_ptr<HttpClient> httpClient = std::make_shared<HttpClient>();
    Player* player = new Player();
}
