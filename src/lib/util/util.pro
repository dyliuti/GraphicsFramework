QT += core gui widgets
TEMPLATE = lib
DEFINES += UTIL_LIBRARY YMW_LIBRARY

ymw += resource
CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

HEADERS += \
    fileutil.h \
    imageutil.h \
    jsonutil.h \
    mathutil.h \
    opengl/buffer.h \
    opengl/framebufferobject.h \
    opengl/glutil.h \
    opengl/shaderprogram.h \
    opengl/texture.h \
    opengl/texturedrawer.h \
    opengl/textureloader.h \
    opengl/vertexarrayobject.h \
    opengl/videoframe.h \
    opengl/viewport.h \
    private/SystemStatusBasePrivate.h \
    singletonmacrodef.h \
    systemstatus.h \
    util.h \
    util_global.h

SOURCES += \
    fileutil.cpp \
    imageutil.cpp \
    jsonutil.cpp \
    mathutil.cpp \
    opengl/buffer.cpp \
    opengl/framebufferobject.cpp \
    opengl/glutil.cpp \
    opengl/shaderprogram.cpp \
    opengl/texture.cpp \
    opengl/texturedrawer.cpp \
    opengl/textureloader.cpp \
    opengl/vertexarrayobject.cpp \
    opengl/videoframe.cpp \
    opengl/viewport.cpp \
    private/SystemStatusBasePrivate.cpp \
    systemstatus.cpp \
    util.cpp

win32 {
    HEADERS += \
        private/systemstatus_win.h

    SOURCES += \
        private/systemstatus_win.cpp \
}

macx {
    HEADERS += \
        private/systemstatus_mac.h

    SOURCES += \
        private/systemstatus_mac.cpp \
}

unix:!macx {
    HEADERS += \
        private/systemstatus_linux.h

    SOURCES += \
        private/systemstatus_linux.cpp
}

include(../../../framework.pri)

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target


