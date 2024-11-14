QT = core gui multimedia network

greaterThan(QT_MAJOR_VERSION, 5): QT += widgets

CONFIG += c++20

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    components/AuthorCard.cpp \
    components/Footer.cpp \
    components/Header.cpp \
    components/HoverIconButton.cpp \
    components/HoverIconButtonWithStages.cpp \
    components/MainInteractSection.cpp \
    components/MusicCard.cpp \
    components/MusicSlider.cpp \
    components/SideBar.cpp \
    components/SoundButton.cpp \
    components/VolumeSlider.cpp \
    \
    pages/SearchPage.cpp \
    \
    utils/CoverFunks.cpp \
    utils/GlobalVariables.cpp \
    utils/HttpClient.cpp \
    utils/MusicClass.cpp \
    utils/Player.cpp \
    utils/UserClasses.cpp \
    \
    windows/LogInWindow.cpp \
    windows/MainWindow.cpp \
    windows/SignUpWindow.cpp \
    \
    main.cpp \
    app.cpp \

HEADERS += \
    headers/app.h \
    \
    headers/components/AuthorCard.h \
    headers/components/Footer.h \
    headers/components/Header.h \
    headers/components/HoverIconButton.h \
    headers/components/HoverIconButtonWithStages.h \
    headers/components/MainInteractSection.h \
    headers/components/MusicCard.h \
    headers/components/MusicSlider.h \
    headers/components/SideBar.h \
    headers/components/SoundButton.h \
    headers/components/VolumeSlider.h \
    \
    headers/utils/HttpClient.h \
    headers/utils/MusicClass.h \
    headers/utils/Player.h \
    headers/utils/globalVariables.h \
    headers/utils/coverFunks.h \
    headers/utils/UserClasses.h \
    \
    headers/windows/MainWindow.h \
    headers/windows/LogInWindow.h \
    headers/windows/SignUpWindow.h \
    \
    headers/pages/SearchPage.h \

FORMS += \
    app.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    assets.qrc \
