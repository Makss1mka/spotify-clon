#include "../headers/components/MainInteractSection.h"
#include "../headers/utils/ContentLoader.h"
#include "../headers/components/SideBar.h"

const int ContentLoader::RELOAD_MUSICS = 1;
const int ContentLoader::RELOAD_AUTHORS = 2;
ContentLoader::ContentLoader() {}

void ContentLoader::connectPageDist(MainInteractSection* pageDist) {
    this->pageDist = pageDist;
}

void ContentLoader::connectSideBar(SideBar* sideBar) {
    this->sideBar = sideBar;
}

void ContentLoader::loadPage(QWidget *pageWidget) {
    this->pageDist->loadPage(pageWidget);
}

void ContentLoader::reloadSideBar(int code) {
    if (this->sideBar->getCurrentStage() == code && code == 1) {
        this->sideBar->musicsClicked();
    } else if (this->sideBar->getCurrentStage() == code && code == 2) {
        this->sideBar->authorsClicked();
    }
}
