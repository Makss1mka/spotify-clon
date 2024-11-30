#ifndef WIDGETMANAGER_H
#define WIDGETMANAGER_H

#include "../components/MainInteractSection.h"
#include "../components/SideBar.h"
#include "../app.h"
#include <QWidget>

class WidgetManager {
public:
    explicit WidgetManager();
    //virtual ~ContentLoader() = default;

    static const int RELOAD_MUSICS;
    static const int RELOAD_AUTHORS;

    void connectPageDist(MainInteractSection* pageDist);
    void connectSideBar(SideBar* sideBar);
    void connectApp(App* app);

    void loadPage(QWidget *pageWidget);
    void reloadSideBar(int code);
    void closeApp();
    void collapseApp();
    void collapseInWindowApp();
private:
    MainInteractSection* pageDist;
    SideBar* sideBar;
    App* app;
};

#endif // WIDGETMANAGER_H
