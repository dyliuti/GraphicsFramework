#include "SystemStatusBasePrivate.h"
#include <QDebug>
#include <QApplication>
#include <QTimerEvent>

#define PRINT_INTERVAL 20

SystemStatusBasePrivate::SystemStatusBasePrivate(QObject *parent)
    : QObject{parent}
    , m_isFirstGetData{true}
    , m_count{0}
{
    m_appId = QApplication::applicationPid();
}

SystemStatusBasePrivate::~SystemStatusBasePrivate()
{
    onStop();
}


void SystemStatusBasePrivate::onStart()
{
    if(m_updateTimer.isActive()) {
        return;
    }

    m_updateTimer.start(1000, this);
}

void SystemStatusBasePrivate::onStop()
{
    if(!m_updateTimer.isActive()) {
        return;
    }

    m_updateTimer.stop();
}


void SystemStatusBasePrivate::timerEvent(QTimerEvent *event)
{
    if (event->timerId() != m_updateTimer.timerId()) {
        QObject::timerEvent(event);
        return;
    }

    onStop();

    do {
        QPair<float, float> cpuPair = getCpuInfo();
        float sysCpuValue = cpuPair.first;
        float processCpuValue = cpuPair.second;
        if(sysCpuValue < 0) break;

        emit sigSysCpuUsePercentageChangeSignal(sysCpuValue, processCpuValue);
        m_count++;

        if(m_count < PRINT_INTERVAL) break;

        quint32 memUsed = getCurProcessMemUsed();
        float sysused = getSysMemUsePercentage();
        qInfo() << QString("###### system cpu usage: %1, YmwApp cpu usage: %2").arg(sysCpuValue).arg(processCpuValue);
        qInfo() << QString("###### system mem total: %1, system mem usage: %2, YmwApp mem usage: %3")
                       .arg(getSysTotalMem()).arg(sysused).arg(memUsed);

        QString sLog = QString::fromWCharArray(L"【系统统计】CPU占用率%1%, YmwApp占用率%2%").arg(sysCpuValue).arg(processCpuValue);
        qInfo() << sLog;
        sLog = QString::fromWCharArray(L"【系统统计】总内存%1M, YmwApp占用%2M,内存占用率%3%").arg(getSysTotalMem()).arg(memUsed).arg(sysused);
        qInfo() << sLog;

        emit sigMemcpyUsed(sysused, memUsed);

        emitCustomSignal(memUsed);

        m_count = 0;
    } while(false);

    onStart();

    QObject::timerEvent(event);
}

void SystemStatusBasePrivate::emitCustomSignal(quint32 memUsed)
{

}

