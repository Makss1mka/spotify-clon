#ifndef WIDGETMANAGER_H
#define WIDGETMANAGER_H

#include "../components/MainInteractSection.h"
#include "../components/SideBar.h"
#include <QWidget>

class WidgetManager {
public:
    explicit WidgetManager();
    //virtual ~ContentLoader() = default;

    static const int RELOAD_MUSICS;
    static const int RELOAD_AUTHORS;

    void connectPageDist(MainInteractSection* pageDist);
    void connectSideBar(SideBar* sideBar);
    void loadPage(QWidget *pageWidget);
    void reloadSideBar(int code);
private:
    MainInteractSection* pageDist;
    SideBar* sideBar;
};

#endif // WIDGETMANAGER_H
