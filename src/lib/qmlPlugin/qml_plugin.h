#ifndef QML_PLUGIN_H
#define QML_PLUGIN_H

#include <QQmlExtensionPlugin>

class QmlPlugin : public QQmlExtensionPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID QQmlExtensionInterface_iid)

public:
    void registerTypes(const char *uri) override;
};

#endif // QML_PLUGIN_H
