QT = core network sql

CONFIG += c++20 cmdline

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        src/adminModule/AdminProvider.cpp \
        src/adminModule/AdminRouter.cpp \
        src/concepts/Provider.cpp \
        src/concepts/Request.cpp \
        src/concepts/Response.cpp \
        src/concepts/Router.cpp \
        src/concepts/RouterDispatcher.cpp \
        src/concepts/Server.cpp \
        src/musicModule/MusicProvider.cpp \
        src/musicModule/MusicRouter.cpp \
        src/userModule/UserProvider.cpp \
        src/userModule/UserRouter.cpp \
        \
        src/main.cpp \
        \
        src/utils/EnvFile.cpp \
        src/utils/exceptions.cpp \
        src/utils/statusCodes.cpp


HEADERS += \
        \
        src/headers/adminModule/AdminProvider.h \
        src/headers/adminModule/AdminRouter.h \
        \
        src/headers/userModule/UserProvider.h \
        src/headers/userModule/UserRouter.h \
        \
        src/headers/concepts/Provider.h \
        src/headers/concepts/Request.h \
        src/headers/concepts/Response.h \
        src/headers/concepts/Router.h \
        src/headers/concepts/RouterDispatcher.h \
        src/headers/concepts/Server.h \
        \
        src/headers/musicModule/MusicProvider.h \
        src/headers/musicModule/MusicRouter.h \
        \
        src/headers/utils/EnvFile.h \
        src/headers/utils/Map.h \
        src/headers/utils/exceptions.h \
        src/headers/utils/statusCodes.h

RESOURCES += \
    resources.qrc

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
