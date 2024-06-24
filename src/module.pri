!isEmpty(MODULE_PRI_INCLUDED):error("module.pri already included in $$basename(_PRO_FILE_)")
MODULE_PRI_INCLUDED = 1

### define avaliable ymw module list
avaliable_modules += board qmlplugin widgetbase util resource

win32 {
    !contains(QMAKE_TARGET.arch, x86_64) {
        _platform_type = win7
    } else {
        _platform_type = x64
    }
}

macx {
    contains(QMAKE_APPLE_DEVICE_ARCHS, arm64) | contains(QMAKE_HOST.arch, arm64) {
        _platform_type = mac-arm64
    } else {
        _platform_type = mac
    }
}

### define fuctions
defineTest(check_pro_exist) {
    project_file = $${1}

    !exists($$project_file): error("[$${project_file}] not exist, please check your source")

    return (true)
}

defineTest(check_pro_exist_if_need) {
    project_file = $${1}
    module = $${2}

    contains(DEFINES, $$module) {
        message("filter submodule: $${module} enabled")
        return (false)
    }

    !exists($$project_file): {
        error("[$${project_file}] not exist, please check your source or enabled [$${module}] in modulefilter_config.pri.")
    }

    return (true)
}

# D:/Code2/Demo/Plugin/ymwPluginRelease/qrelease
isEmpty(lib_root){ # if $$lib_root not set, set it. $$OUTPUT_PWD may be comes from framework.pri
    win32:lib_root = $$OUTPUT_PWD
    macx:lib_root = $$OUTPUT_PWD/$$TARGET_BUNDLE_NAME/Contents/Library
    unix:!macx:lib_root = $$OUTPUT_PWD/lib
}

# check module is avaliable
for (module, ymw) {
    _lower_module_name = $$lower($$module)

    !contains(avaliable_modules, $$_lower_module_name) {
        for(_module, avaliable_modules) {
            equals(_lower_module_name, ymw$${_module}): _lower_module_name = $${_module}
            _avaliable_modules_prepend_ymw += ymw$${_module}
        }

        contains(_avaliable_modules_prepend_ymw, $$lower($$module)) {
            warning(module: [$$module] processed as [$${_lower_module_name}])
        } else {
            error(can not find module: [$$module])
        }
    }

    enabled_modules *= $${_lower_module_name}
}

# print current pro enabled module list
!build_pass:!isEmpty(enabled_modules):message($$basename(_PRO_FILE_) enabled modules: $$enabled_modules)

# set output path as lib path
LIBS *= -L$${lib_root}
exists($${lib_root}/plugins): -L$${lib_root}/plugins
message("777777 $${lib_root}/plugins")
### define each module that can use

# board
contains(enabled_modules, board){
    INCLUDEPATH *= $$PWD/lib
    INCLUDEPATH *= $$PWD/lib/board

    LIBS += -lboard
}

# qmlplugin
contains(enabled_modules, qmlplugin){
    QML_IMPORT_PATH = $$OUTPUT_PWD

    LIBS += -L$$OUTPUT_PWD/qmlPlugin -lqmlPlugin
}

# util
contains(enabled_modules, util){
    INCLUDEPATH *= $$PWD/lib
    INCLUDEPATH *= $$PWD/lib/util

    LIBS += -L$$OUTPUT_PWD/util -lutil
}

# util
contains(enabled_modules, resource){
    INCLUDEPATH *= $$PWD/resource

    LIBS += -L$$OUTPUT_PWD/resource -lresource
}
