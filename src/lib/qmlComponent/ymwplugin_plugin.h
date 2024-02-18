#ifndef YMWPLUGIN_PLUGIN_H
#define YMWPLUGIN_PLUGIN_H

#include <QQmlExtensionPlugin>

class YmwPluginPlugin : public QQmlExtensionPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID QQmlExtensionInterface_iid)

public:
    void registerTypes(const char *uri) override;
};

#endif // YMWPLUGIN_PLUGIN_H
