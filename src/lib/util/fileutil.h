#ifndef EEOFILEUTIL_H
#define EEOFILEUTIL_H
#include <QString>
#include "util_global.h"
#include <QObject>

class UTIL_EXPORT FileUtil
{
public:
    static QString getErrorFileDir();
    static bool exist(const QString &path);
    /*
     * 传入路径是否为文件夹
     */
    static Q_INVOKABLE bool isDir(const QString& path);
    static bool makePath(const QString &strDirPath, bool skipExistingPath = true);
    static bool deleteRecursively(const QString &path);
    static bool copyRecursively(const QString &srcFilePath, const QString &tgtFilePath, bool overwrite);
    static QStringList getTypicalFiles(const QString &strDirPath, const QStringList &strSuffixes, bool bRecursively);
    static QString getName(const QString &path);

    /*
     * 文件路径前缀
     */
    static Q_INVOKABLE QString removeFilePrefix(const QString& strFilePath);
    static Q_INVOKABLE QString addFilePrefix(const QString& strFilePath);

    /*
     * 删除qrc:前缀
     */
    static QString removeQrcPrefix(const QString& filePath);
};

#endif // EEOFILEUTIL_H
