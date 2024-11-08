QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    components/authorCard.cpp \
    components/header.cpp \
    components/mainInteractSection.cpp \
    components/player.cpp \
    components/musicCard.cpp \
    components/sideBar.cpp \
    \
    pages/searchPage.cpp \
    \
    windows/signUpWindow.cpp \
    windows/logInWindow.cpp \
    windows/mainWindow.cpp \
    \
    utils/coverFunks.cpp\
    \
    main.cpp \
    app.cpp \

HEADERS += \
    headers/app.h \
    \
    headers/components/AuthorCard.h \
    headers/components/Header.h \
    headers/components/MainInteractSection.h \
    headers/components/Player.h \
    headers/components/MusicCard.h \
    headers/components/SideBar.h \
    \
    headers/windows/MainWindow.h \
    headers/windows/LogInWindow.h \
    headers/windows/SignUpWindow.h \
    \
    headers/pages/SearchPage.h \
    \
    headers/utils/coverFunks.h

FORMS += \
    app.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    assets.qrc \
    components/resources.qrc
