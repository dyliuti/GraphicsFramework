TEMPLATE = subdirs

SUBDIRS += src/resource
SUBDIRS += src/lib/util
SUBDIRS += src/lib/render
SUBDIRS += src/lib/qmlplugin
SUBDIRS += src/lib/widget
SUBDIRS += src/lib/board
SUBDIRS += src/main

# resource
resource.file = $$PWD/src/resource/resource.pro
# util
util.file = $$PWD/src/lib/util/util.pro
util.depands += resource
# render
render.file = $$PWD/src/lib/render/render.pro
render.depands += util

CONFIG += ordered


