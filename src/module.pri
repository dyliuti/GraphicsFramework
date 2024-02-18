!isEmpty(MODULE_PRI_INCLUDED):error("module.pri already included in $$basename(_PRO_FILE_)")
MODULE_PRI_INCLUDED = 1

### define avaliable ymw module list
avaliable_modules += board qmlplugin widgetbase

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

#defineTest(copySharedLib) {
#    win32: _lib_name = $${1}.dll
#    macx: _lib_name = lib$${1}.dylib

#    _sub_dir = $${2}

#    _lib_src_path = $${sharedlib_root}/$${_platform_type}

#    isEmpty(_sub_dir) {
#        _lib_target_path = $${lib_root}
#    } else {
#        _lib_src_path = $${_lib_src_path}/$${_sub_dir}
#        _lib_target_path = $${lib_root}/$${_sub_dir}
#    }

#    !exists($${_lib_target_path}): mkpath($${_lib_target_path})

#    SRC_FILE = $${_lib_src_path}/$${_lib_name}
#    TARGET_FILE = $${_lib_target_path}/$${_lib_name}

#    win32 {
#        SRC_FILE ~= s,/,\\,g
#        TARGET_FILE ~= s,/,\\,g
#    }

##    message("src: $$SRC_FILE")
##    message("target: $$TARGET_FILE")

#    win32 {
#        QMAKE_POST_LINK += $$quote($${QMAKE_COPY_FILE} $${SRC_FILE} $${TARGET_FILE}$$escape_expand(\n\t))
#    }
#    macx {
#        QMAKE_POST_LINK += $$quote($${QMAKE_COPY_FILE} -a $${SRC_FILE} $${TARGET_FILE}$$escape_expand(\n\t))
#    }
#    export(QMAKE_POST_LINK)
#    return(true)
#}

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
            error(can not find eeo module: [$$module])
        }
    }

    enabled_modules *= $${_lower_module_name}
}

# print current pro enabled module list
!build_pass:!isEmpty(enabled_modules):message($$basename(_PRO_FILE_) enabled eeomodules: $$enabled_modules)

# set output path as lib path
LIBS *= -L$${lib_root}
exists($${lib_root}/plugins): -L$${lib_root}/plugins
message("777777 $${lib_root}/plugins")
### define each module that can use

# extensionsystem
contains(enabled_modules, board){
    INCLUDEPATH *= $$PWD/lib
    INCLUDEPATH *= $$PWD/lib/board

    LIBS += -lboard
}

contains(enabled_modules, qmlplugin){
    QML_IMPORT_PATH = $$OUTPUT_PWD

    LIBS += -L$$OUTPUT_PWD/qmlPlugin -lqmlPlugin
}

# update deploy timestame
#contains(enabled_modules, forcerebuild) {
#    STAMP_FILE = $$PWD/deploy.stamp
#    win32 {
#        STAMP_FILE ~= s,/,\\,g
#        QMAKE_POST_LINK += $$quote(copy /b $${STAMP_FILE}+,, > nul$$escape_expand(\n\t))
#    } else {
#        QMAKE_POST_LINK += $$quote(touch $${STAMP_FILE}$$escape_expand(\n\t))
#    }
#    PRE_TARGETDEPS += $$PWD/deploy.stamp
#}

#unix:!macx: QMAKE_PRE_LINK += $$quote(/bin/bash $$PWD/thirdparty/linux_build_prepare.sh $$lib_root $$escape_expand(\n\t))
