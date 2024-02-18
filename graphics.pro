TEMPLATE = subdirs

SUBDIRS += src/lib/qmlPlugin
pro_file = $$PWD/src/lib/qmlPlugin/qmlPlugin.pro

SUBDIRS += src/lib/widget
pro_file = $$PWD/src/lib/widget/widget.pro

SUBDIRS += src/lib/board
pro_file = $$PWD/src/lib/board/board.pro

SUBDIRS += src/main
pro_file = $$PWD/src/main.pro

CONFIG += ordered


