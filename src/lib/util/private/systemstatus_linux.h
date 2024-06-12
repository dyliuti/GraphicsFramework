#ifndef SYSTEMSTATUSPRIVATE_H
#define SYSTEMSTATUSPRIVATE_H

#include <QBasicTimer>
#include "SystemStatusBasePrivate.h"

class SystemStatusPrivate : public SystemStatusBasePrivate
{
    Q_OBJECT

public:
    explicit SystemStatusPrivate(QObject *parent = 0);
    ~SystemStatusPrivate();

public:
    QPair<float, float> getCpuInfo() override;
    float getSysMemUsePercentage() override;
    float getSysTotalMem() override;
    QPair<float, float> getCpuUsePercentage() override;
    qint32 getCurProcessMemUsed() override;

private:
    float getSysCpuUsePercentage();
};

#endif // SYSTEMSTATUSPRIVATE_H
