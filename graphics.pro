TEMPLATE = subdirs

SUBDIRS += src/resource
SUBDIRS += src/lib/util
#SUBDIRS += src/lib/qmlPlugin

SUBDIRS += src/lib/widget
pro_file = $$PWD/src/lib/widget/widget.pro

SUBDIRS += src/lib/board
pro_file = $$PWD/src/lib/board/board.pro

SUBDIRS += src/main
pro_file = $$PWD/src/main.pro

CONFIG += ordered


