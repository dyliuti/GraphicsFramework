#ifndef SYSTEMSTATUSPRIVATE_H
#define SYSTEMSTATUSPRIVATE_H

#include <QObject>
#include <mach/mach.h>


#include "SystemStatusBasePrivate.h"


class SystemStatusPrivate : public SystemStatusBasePrivate
{
    Q_OBJECT

public:
    explicit SystemStatusPrivate(QObject *parent = 0);
    ~SystemStatusPrivate();


    float getSysCpuUsePercentage();
    float getProcessCpuUsePercentage();

    QPair<float, float> getCpuInfo() override;
    qint32 getCurProcessMemUsed() override;
    QPair<float, float> getCpuUsePercentage() override;
    float getSysTotalMem() override;
    float getSysMemUsePercentage() override;

private:



    host_cpu_load_info_data_t m_cpuLoad;

};

#endif // SYSTEMSTATUSPRIVATE_H
