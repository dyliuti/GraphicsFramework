#include "fileutil.h"
#include <QDir>
#include <QStandardPaths>
#include <QFileInfo>
#include <QDebug>

QString FileUtil::getErrorFileDir()
{
    QString homeworkDirPath = QDir::toNativeSeparators(QString("%1/error").arg(QStandardPaths::writableLocation(QStandardPaths::AppDataLocation)));
    QDir homeworkDir(homeworkDirPath);
    if (!homeworkDir.exists()) {
        homeworkDir.mkpath(homeworkDirPath);
    }

    return homeworkDirPath;
}

bool FileUtil::exist(const QString &path)
{
    return QFileInfo(path).exists();
}

bool FileUtil::isDir(const QString &path)
{
    return QFileInfo(path).isDir();
}

bool FileUtil::makePath(const QString &strDirPath, bool skipExistingPath)
{
    if (skipExistingPath && exist(strDirPath)) {
        return true;
    }

    return QDir().mkpath(strDirPath);
}

bool FileUtil::deleteRecursively(const QString &path)
{
    QFileInfo fileInfo(path);
    if (fileInfo.isDir()) {
        return QDir(path).removeRecursively();
    } else {
        return QFile(path).remove();
    }
}

bool FileUtil::copyRecursively(const QString &srcFilePath, const QString &tgtFilePath, bool overwrite)
{
    if (!exist(srcFilePath) || srcFilePath.isEmpty()) {
        qDebug() << __FUNCTION__ << " file is not exist : " << srcFilePath;
        return false;
    }
    QFileInfo srcFileInfo(srcFilePath);
    if (srcFileInfo.isDir()) {
        QDir targetDir(tgtFilePath);
        if (!targetDir.exists()) {
            bool bMakePath = makePath(tgtFilePath);
            if (!bMakePath)
                return false;
        }
        QDir sourceDir(srcFilePath);
        QStringList fileNames = sourceDir.entryList(QDir::Files | QDir::Dirs | QDir::NoDotAndDotDot | QDir::Hidden | QDir::System);
        foreach (const QString &fileName, fileNames) {
            const QString newSrcFilePath = srcFilePath + QLatin1Char('/') + fileName;
            const QString newTgtFilePath = tgtFilePath + QLatin1Char('/') + fileName;
            if (!copyRecursively(newSrcFilePath, newTgtFilePath, overwrite))
                return false;
        }
    } else {
        if (overwrite && QFile::exists(tgtFilePath)) {
            QFile::remove(tgtFilePath);
        }
        if (!QFile::copy(srcFilePath, tgtFilePath)) {
            if (!exist(srcFilePath))
                return false;
            QFileInfo info(tgtFilePath);
            QDir dir = info.dir();
            if (!dir.exists())
                makePath(dir.absolutePath());
            if (!QFile::copy(srcFilePath, tgtFilePath))
                return false;
        } else {
            QFile(tgtFilePath).setPermissions(QFile::WriteOther | QFile::ReadOther | QFile::WriteOwner | QFile::ReadOwner | QFile::WriteUser | QFile::ReadUser | QFile::WriteGroup | QFile::ReadGroup);
        }
    }
    return true;
}

QStringList FileUtil::getTypicalFiles(const QString &strDirPath, const QStringList &strSuffixes, bool bRecursively)
{
    QStringList result;
    QDir dir(strDirPath);
    if (!dir.exists()) {
        return result;
    }

    const QFileInfoList &subFileInfos = dir.entryInfoList(strSuffixes, QDir::Files | QDir::Dirs | QDir::NoDotAndDotDot | QDir::Hidden | QDir::System);
    for (const QFileInfo &subFileInfo : subFileInfos) {
        if (subFileInfo.isFile()) {
            result.append(subFileInfo.absoluteFilePath());
        }
    }

    if (bRecursively) {
        const QFileInfoList &subDirInfos = dir.entryInfoList(QStringList(), QDir::Dirs | QDir::NoDotAndDotDot | QDir::Hidden | QDir::System);
        for (const QFileInfo &subDirInfo : subDirInfos) {
            result.append(getTypicalFiles(subDirInfo.absoluteFilePath(), strSuffixes, bRecursively));
        }
    }

    return result;
}

QString FileUtil::getName(const QString &path)
{
    QFileInfo fileInfo(path);
    if (fileInfo.isDir() || path.endsWith("/")) {
        return QDir(path).dirName();
    } else {
        return fileInfo.fileName();
    }
}


QString FileUtil::addFilePrefix(const QString& filePath)
{
#ifdef Q_OS_WIN
    static const QString c_strFilePrefix = "file:///";
#else
    static const QString c_strFilePrefix = "file://";
#endif

    if (filePath.startsWith(c_strFilePrefix))
    {
        return filePath;
    }
    else
    {
        return c_strFilePrefix + filePath;
    }
}


QString FileUtil::removeFilePrefix(const QString& filePath)
{
#ifdef Q_OS_WIN
    static const QString c_strFilePrefix = "file:///";
#else
    static const QString c_strFilePrefix = "file://";
#endif

    if (filePath.startsWith(c_strFilePrefix))
    {
        return filePath.right(filePath.length() - c_strFilePrefix.length());
    }
    else
    {
        return filePath;
    }
}

QString FileUtil::removeQrcPrefix(const QString& filePath)
{
    if (filePath.startsWith("qrc:"))
    {
        return filePath.right(filePath.size() - 3);
    }
    return filePath;
}
