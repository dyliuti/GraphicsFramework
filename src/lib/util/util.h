#ifndef UTIL_H
#define UTIL_H

#include "util_global.h"
#include <QSystemSemaphore>

class UTIL_EXPORT Util {
public:
    static bool processExist(unsigned long processID, const std::wstring& processName);
    static QString getAppVersion();
};

#endif // UTIL_H
