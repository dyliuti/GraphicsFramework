#include "jsonutil.h"
#include <QJsonDocument>
#include <QDebug>


QJsonObject JsonUtil::convertStringToJsonObj(const QString &json)
{
    QJsonDocument jsonDocument = QJsonDocument::fromJson(json.toUtf8().data());
    if (jsonDocument.isNull() || !jsonDocument.isObject())
    {
        return QJsonObject();
    }

    return jsonDocument.object();
}

QString JsonUtil::convertJsonObjToString(const QJsonObject &obj)
{
    QJsonDocument doc(obj);
    return doc.toJson();
}
