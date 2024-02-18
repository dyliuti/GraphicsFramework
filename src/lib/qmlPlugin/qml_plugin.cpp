#include "qml_plugin.h"

#include "myitem.h"

#include <qqml.h>

void QmlPlugin::registerTypes(const char *uri)
{
    // @uri qmlPlugin
    qmlRegisterType<MyItem>(uri, 1, 0, "MyItem");
}

