#ifndef SYSTEMSTATUSPRIVATE_H
#define SYSTEMSTATUSPRIVATE_H

#include <QObject>
#define _WINSOCKAPI_
#include <windows.h>

#include "SystemStatusBasePrivate.h"

class SystemStatusPrivate : public SystemStatusBasePrivate
{
    Q_OBJECT

public:
    explicit SystemStatusPrivate(QObject *parent = 0);
    ~SystemStatusPrivate();

    QPair<float, float> getCpuInfo() override;
    void emitCustomSignal(quint32 memUsed) override;
    float getSysMemUsePercentage() override;
    qint32 getCurProcessMemUsed() override;
    QPair<float, float> getCpuUsePercentage() override;
    float getSysTotalMem() override;

private:
    HANDLE m_hProcess;

    FILETIME m_preIdleTime;
    FILETIME m_preKernelTime;
    FILETIME m_preUserTime;

    FILETIME m_preProcessKernelTime;
    FILETIME m_preProcessUserTime;
};

#endif // SYSTEMSTATUSPRIVATE_H
