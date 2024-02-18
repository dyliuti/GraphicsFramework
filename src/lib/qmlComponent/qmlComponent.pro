TEMPLATE = lib
TARGET = YmwPlugin
QT += qml quick
CONFIG += plugin c++11

DEFINES += QML_PLUGIN
TARGET = $$qtLibraryTarget($$TARGET)
uri = YmwPlugin  # 因为PLUGIN_PARENT_PATH 中生成qmltypes的目录就是uri，不相同，如com.ymw.qmlcpmponents的话生成就不再一个目录下了，而且还会有生成问题

# Input
win32 {
    HEADERS += $$system(for /r $$PWD %i in (*.h,*.hpp) do @echo %i)
    SOURCES += $$system(for /r $$PWD %i in (*.c,*.cpp) do @echo %i)
    FORMS += $$system(for /r $$PWD %i in (*.ui) do @echo %i)
}

include(../../../framework.pri)
include(../../module.pri)

DISTFILES = qmldir
message("222222: $$OUTPUT_PWD")  # OUT_PWD 不是 OUTPUT_PWD
QML_PLUGIN_OUTPUT_DIR = $$OUTPUT_PWD/YmwPlugin
!equals(_PRO_FILE_PWD_, $$QML_PLUGIN_OUTPUT_DIR) {
    copy_qmldir.target = $$QML_PLUGIN_OUTPUT_DIR/qmldir
    copy_qmldir.depends = $$_PRO_FILE_PWD_/qmldir
    copy_qmldir.commands = $(COPY_FILE) "$$replace(copy_qmldir.depends, /, $$QMAKE_DIR_SEP)" "$$replace(copy_qmldir.target, /, $$QMAKE_DIR_SEP)"
    QMAKE_EXTRA_TARGETS += copy_qmldir
    PRE_TARGETDEPS += $$copy_qmldir.target
}

qmldir.files = qmldir

RESOURCES += \
  qml.qrc

message("333333: $$QML_PLUGIN_OUTPUT_DIR $$[QT_HOST_PREFIX]")
# C:/APP/Qt5.15.1/5.15.1/msvc2019/bin/qmlplugindump.exe com/ymw 1.0 C:/Code/Demo/qmlLibraryRelease/qrelease/YmwPlugin/../ > C:/Code/Demo/qmlLibraryRelease/qrelease/YmwPlugin/plugin.qmltypes
PLUGIN_NAME          = $$uri  #com.ymw.qmlcomponents
PLUGIN_VERSION       = 1.0
PLUGIN_PARENT_PATH   = $$QML_PLUGIN_OUTPUT_DIR/../ # C:/Code/Demo/qmlLibraryDebug/qrelease/YmwPlugin/../
PLUGIN_QMLTYPES_PATH = $$QML_PLUGIN_OUTPUT_DIR/plugin.qmltypes # C:/Code/Demo/qmlLibraryDebug/qdebug/YmwPlugin/plugin.qmltypes
QMAKE_POST_LINK += $$system($$quote($$[QT_HOST_PREFIX]/bin/qmlplugindump.exe -nonrelocatable $$PLUGIN_NAME \"$$PLUGIN_VERSION\" \"$$PLUGIN_PARENT_PATH\" > \"$$PLUGIN_QMLTYPES_PATH\"))

unix {
    installPath = $$[QT_INSTALL_QML]/$$replace(uri, \., /)
    qmldir.path = $$installPath
    target.path = $$installPath
    INSTALLS += target qmldir
}
