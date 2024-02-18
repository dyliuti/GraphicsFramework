TEMPLATE = lib

QT += qml quick
CONFIG += plugin c++17
DEFINES += QML_PLUGIN

#TARGET = $$qtLibraryTarget($$TARGET)
TARGET = qmlPlugin
TARGET = $$qtLibraryTarget($$TARGET)
uri = qmlPlugin

# Input
win32 {
    HEADERS += $$system(for /r $$PWD %i in (*.h,*.hpp) do @echo %i)
    SOURCES += $$system(for /r $$PWD %i in (*.c,*.cpp) do @echo %i)
    FORMS += $$system(for /r $$PWD %i in (*.ui) do @echo %i)
}

include(../../../framework.pri)
include(../../module.pri)

DISTFILES = qmldir
QML_PLUGIN_OUTPUT_DIR = $$OUTPUT_PWD/qmlPlugin
!equals(_PRO_FILE_PWD_, $$QML_PLUGIN_OUTPUT_DIR) {
    copy_qmldir.target = $$QML_PLUGIN_OUTPUT_DIR/qmldir
    copy_qmldir.depends = $$_PRO_FILE_PWD_/qmldir
    copy_qmldir.commands = $(COPY_FILE) "$$replace(copy_qmldir.depends, /, $$QMAKE_DIR_SEP)" "$$replace(copy_qmldir.target, /, $$QMAKE_DIR_SEP)"
    QMAKE_EXTRA_TARGETS += copy_qmldir
    PRE_TARGETDEPS += $$copy_qmldir.target
}

qmldir.files = qmldir
unix {
    installPath = $$[QT_INSTALL_QML]/$$replace(uri, \., /)
    qmldir.path = $$installPath
    target.path = $$installPath
    INSTALLS += target qmldir
}

PLUGIN_NAME          = $$uri
PLUGIN_VERSION       = 1.0
PLUGIN_PARENT_PATH   = $$QML_PLUGIN_OUTPUT_DIR/../
PLUGIN_QMLTYPES_PATH = $$QML_PLUGIN_OUTPUT_DIR/qmlplugin.qmltypes
QMAKE_POST_LINK += $$system($$quote($$[QT_HOST_PREFIX]/bin/qmlplugindump.exe -nonrelocatable $$PLUGIN_NAME \"$$PLUGIN_VERSION\" \"$$PLUGIN_PARENT_PATH\" > \"$$PLUGIN_QMLTYPES_PATH\"))

