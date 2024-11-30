#include "../headers/components/MainInteractSection.h"
#include "../headers/utils/WidgetManager.h"
#include "../headers/components/SideBar.h"

const int WidgetManager::RELOAD_MUSICS = 1;
const int WidgetManager::RELOAD_AUTHORS = 2;
WidgetManager::WidgetManager() {}

void WidgetManager::connectPageDist(MainInteractSection* pageDist) {
    this->pageDist = pageDist;
}

void WidgetManager::connectSideBar(SideBar* sideBar) {
    this->sideBar = sideBar;
}

void WidgetManager::loadPage(QWidget *pageWidget) {
    this->pageDist->loadPage(pageWidget);
}

void WidgetManager::reloadSideBar(int code) {
    if (this->sideBar->getCurrentStage() == code && code == 1) {
        this->sideBar->musicsClicked();
    } else if (this->sideBar->getCurrentStage() == code && code == 2) {
        this->sideBar->authorsClicked();
    }
}
