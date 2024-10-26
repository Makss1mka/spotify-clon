QT = core network

CONFIG += c++20 cmdline

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        src/concepts/request.cpp \
        src/main.cpp \
        src/concepts/server.cpp \
        src/concepts/router.cpp \
        src/concepts/routerDispatcher.cpp \
        src/handlers/userRouter.cpp \
        src/utils/parsers.cpp

HEADERS += \
        src/headers/concepts/Request.h \
        src/headers/concepts/Router.h \
        src/headers/concepts/RouterDispatcher.h \
        src/headers/concepts/Server.h \
        src/headers/handlers/userRouter.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
