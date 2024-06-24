#ifndef SYSTEMSTATUS_H
#define SYSTEMSTATUS_H

#include "util_global.h"
#include <QObject>

class QThread;
class SystemStatusPrivate;
class UTIL_EXPORT SystemStatus : public QObject
{
    Q_OBJECT
//    Q_DISABLE_COPY_MOVE(SystemStatus)

public:
    explicit SystemStatus(QObject *parent = 0);
    ~SystemStatus();
    static SystemStatus *instance();
    static void release();

signals:
    void sigSysCpuUsePercentageChangeSignal(float value, float processCpuUsage);
    void sigMemcpyUsed(float sysMemUsePercentage, quint32 curprocessused);
    void sigMemUsedOverflow(quint32 used);

public:
    void startCheckStatus();
    void stopCheckStatus();

public:
    float getSysMemUsePercentage();

    /**
     * Get system TotalPhys memory size
     * eg. return 16268 (MB)
     */
    float getSysTotalMem();

    /*
    * Get Current process used phyMemory size
    * eg. return   104(MB)
    */
    qint32 getCurProcessMemUsed();

    QPair<float, float> getCpuUsePercentage(); // <totalCpu, processCpu>

private:
    QThread *m_thread = nullptr;
    SystemStatusPrivate *m_p = nullptr;
};

#endif // SYSTEMSTATUS_H
