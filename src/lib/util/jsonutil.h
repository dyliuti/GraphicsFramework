#ifndef EEOJSONUTIL_H
#define EEOJSONUTIL_H
#include <QString>
#include <QJsonObject>
#include "util_global.h"

class UTIL_EXPORT JsonUtil
{
public:
    static QJsonObject convertStringToJsonObj(const QString& json);
    static QString convertJsonObjToString(const QJsonObject& obj);
};

#endif // EEOJSONUTIL_H
