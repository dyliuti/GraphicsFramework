QT -= gui

TEMPLATE = lib
DEFINES += RESOURCE_LIBRARY YMW_LIBRARY

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    resource.cpp

HEADERS += \
    resource_global.h \
    resource.h

include(../../../framework.pri)

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    image.qrc \
    qss.qrc \
    shader.qrc
