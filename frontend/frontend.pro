QT = core gui multimedia network

greaterThan(QT_MAJOR_VERSION, 5): QT += widgets

CONFIG += c++20

# Укажите путь к заголовочным файлам SFML
INCLUDEPATH += $$PWD/external/sfml/include

# Укажите путь к библиотекам SFML
LIBS += -L$$PWD/external/sfml/lib

# Подключите необходимые библиотеки SFML
LIBS += -lsfml-audio -lsfml-system

# Дополнительные системные библиотеки для Windows
LIBS += -lopengl32 -lwinmm

# Определите, где искать динамические библиотеки во время выполнения (для Windows)
win32:CONFIG(release, debug|release): PATH += $$PWD/bin
win32:CONFIG(debug, debug|release): PATH += $$PWD/bin

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
    pages/AuthorPage.cpp \
    pages/MusicAddPage.cpp \
    pages/MusicPage.cpp \
    pages/SearchPage.cpp \
    \
    pages/UserPage.cpp \
    utils/CoverFunks.cpp \
    utils/GlobalVariables.cpp \
    utils/HttpClient.cpp \
    utils/MusicClass.cpp \
    utils/Player.cpp \
    utils/UserClasses.cpp \
    utils/EnvFile.cpp \
    \
    utils/WidgetManager.cpp \
    windows/LoginSignupWindow.cpp \
    windows/MainWindow.cpp \
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
    headers/pages/AuthorPage.h \
    headers/pages/MusicAddPage.h \
    headers/pages/MusicPage.h \
    headers/pages/UserPage.h \
    headers/utils/HttpClient.h \
    headers/utils/MusicClass.h \
    headers/utils/Player.h \
    headers/utils/WidgetManager.h \
    headers/utils/globalVariables.h \
    headers/utils/coverFunks.h \
    headers/utils/UserClasses.h \
    headers/utils/EnvFile.h \
    \
    headers/windows/LoginSignupWindow.h \
    headers/windows/MainWindow.h \
    \
    headers/pages/SearchPage.h \

FORMS += \
    app.ui

# win32 {
#     debug {
#         DESTDIR = $$OUT_PWD/debug
#     }
#     release {
#         DESTDIR = $$OUT_PWD/release
#     }
#     QMAKE_POST_LINK += $$quote(copy /Y $$PWD/bin/sfml-audio-2.dll $$DESTDIR)$$escape_expand(\\n\\t)
#     QMAKE_POST_LINK += $$quote(copy /Y $$PWD/bin/sfml-system-2.dll $$DESTDIR)$$escape_expand(\\n\\t)
#     QMAKE_POST_LINK += $$quote(copy /Y $$PWD/bin/openal32.dll $$DESTDIR)$$escape_expand(\\n\\t)
# }

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    assets.qrc \

windows: LIBS += -lgdi32 -lopengl32 -lwinmm
