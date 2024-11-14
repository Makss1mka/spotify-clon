QT = core gui multimedia network

greaterThan(QT_MAJOR_VERSION, 5): QT += widgets

CONFIG += c++20

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    components/HoverIconButton.cpp \
    components/HoverIconButtonWithStages.cpp \
    components/MusicSlider.cpp \
    components/SoundButton.cpp \
    components/VolumeSlider.cpp \
    components/authorCard.cpp \
    components/footer.cpp \
    components/header.cpp \
    components/mainInteractSection.cpp \
    components/musicCard.cpp \
    components/sideBar.cpp \
    \
    pages/searchPage.cpp \
    \
    utils/globalVariables.cpp \
    utils/httpClient.cpp \
    utils/musicClass.cpp \
    utils/player.cpp \
    utils/coverFunks.cpp\
    \
    windows/signUpWindow.cpp \
    windows/logInWindow.cpp \
    windows/mainWindow.cpp \
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
    \
    headers/components/SoundButton.h \
    headers/components/VolumeSlider.h \
    headers/utils/HttpClient.h \
    headers/utils/MusicClass.h \
    headers/utils/Player.h \
    headers/utils/globalVariables.h \
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
