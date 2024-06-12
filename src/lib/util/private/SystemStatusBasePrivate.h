#ifndef SYSTEMSTATUSBASEPRIVATE_H
#define SYSTEMSTATUSBASEPRIVATE_H

#include <QObject>
#include <QBasicTimer>

enum BYTE_UNITS { BYTES = 0, KILOBYTES = 1, MEGABYTES = 2, GIGABYTES = 3 };

template<class T>
T convert_unit(T num, int to, int from = BYTES)
{
    for (; from < to; from++) {
        num /= 1024;
    }
    return num;
}

class SystemStatusBasePrivate : public QObject
{
    Q_OBJECT
public:
    explicit SystemStatusBasePrivate(QObject *parent = nullptr);
    virtual ~SystemStatusBasePrivate();

signals:
    void sigSysCpuUsePercentageChangeSignal(float value, float processCpuUsage);
    void sigMemcpyUsed(float sysMemUsePercentage, quint32 curprocessused);
    void sigMemUsedOverflow(quint32 used);

public slots:
    void onStart();
    void onStop();

protected:
    void timerEvent(QTimerEvent *event) override;
    virtual QPair<float, float> getCpuInfo() = 0;
    virtual float getSysMemUsePercentage() = 0;
    /**
     * Get system TotalPhys memory size
     * eg. return 16268 (MB)
     */
    virtual float getSysTotalMem() = 0;
    virtual QPair<float, float> getCpuUsePercentage() = 0; // <totalCpu, processCpu>
    /*
    * Get Current process used phyMemory size
    * eg. return   104(MB)
    */
    virtual qint32 getCurProcessMemUsed() = 0;
    virtual void emitCustomSignal(quint32 memUsed);

protected:
    bool m_isFirstGetData;
    bool m_isFirst = true;
    qint64 m_appId;

private:
    QBasicTimer m_updateTimer;
    int m_count = 0;
};

#endif // SYSTEMSTATUSBASEPRIVATE_H
