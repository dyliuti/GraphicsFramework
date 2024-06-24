QT += gui

TEMPLATE = lib
DEFINES += RESOURCE_LIBRARY YMW_LIBRARY

CONFIG += c++17
CONFIG += resources_big
# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

win32 {
    HEADERS += $$system(for /r $$PWD %i in (*.h,*.hpp) do @echo %i)
    SOURCES += $$system(for /r $$PWD %i in (*.c,*.cpp) do @echo %i)
    FORMS += $$system(for /r $$PWD %i in (*.ui) do @echo %i)
}

unix {
    HEADERS += $$system(find $$PWD -name \'*.h\') \
               $$system(find $$PWD -name \'*.hpp\')

    SOURCES += $$system(find $$PWD -name \'*.c\') \
               $$system(find $$PWD -name \'*.cpp\') \
               $$system(find $$PWD -name \'*.mm\')
}

include(../../framework.pri)

QTDIR = $$[QT_HOST_PREFIX]
win32 {
    REAL_RCC = $$QTDIR/bin/rcc.exe
    REAL_RCC ~= s,/,\\,g
}
unix:REAL_RCC = $$QTDIR/bin/rcc
!exists($$REAL_RCC) {
    unix:REAL_RCC = $$QTDIR/libexec/rcc
    win32 {
        REAL_RCC = $$QTDIR/libexec/rcc.exe
        REAL_RCC ~= s,/,\\,g
    }
}
system($$REAL_RCC --binary -o $$PWD/image.res $$PWD/image.qrc)

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    image.qrc
