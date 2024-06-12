#include "systemstatus.h"

//#include <QApplication>
#include <QThread>

#if defined Q_OS_MAC
#include "private/systemstatus_mac.h"
#elif defined Q_OS_WIN
#include "private/systemstatus_win.h"
#elif defined Q_OS_LINUX
#include "private/systemstatus_linux.h"
#endif

Q_GLOBAL_STATIC(SystemStatus, systemStatus)

SystemStatus::SystemStatus(QObject *parent)
    : QObject(parent)
{
    m_p = new SystemStatusPrivate();

    m_thread = new QThread(this);
    m_p->moveToThread(m_thread);
    m_thread->start();

    connect(m_p, &SystemStatusPrivate::sigMemcpyUsed, this, &SystemStatus::sigMemcpyUsed);
    connect(m_p, &SystemStatusPrivate::sigMemUsedOverflow, this, &SystemStatus::sigMemUsedOverflow);
    connect(m_p, &SystemStatusPrivate::sigSysCpuUsePercentageChangeSignal, this, &SystemStatus::sigSysCpuUsePercentageChangeSignal);
}

SystemStatus::~SystemStatus()
{
    stopCheckStatus();

    m_thread->quit();
    m_thread->wait();

    delete m_thread;
    delete m_p;
}

SystemStatus *SystemStatus::instance()
{
    return systemStatus;
}

void SystemStatus::release()
{
    if(systemStatus.exists()) {
        systemStatus->stopCheckStatus();
    }
}

void SystemStatus::startCheckStatus()
{
    QMetaObject::invokeMethod(m_p, "start", Qt::QueuedConnection);
}

void SystemStatus::stopCheckStatus()
{
    QMetaObject::invokeMethod(m_p, "stop", Qt::QueuedConnection);
}

float SystemStatus::getSysMemUsePercentage()
{
    return m_p->getSysMemUsePercentage();
}

float SystemStatus::getSysTotalMem()
{
    return m_p->getSysTotalMem();
}

qint32 SystemStatus::getCurProcessMemUsed()
{
    return m_p->getCurProcessMemUsed();
}

QPair<float, float> SystemStatus::getCpuUsePercentage()
{
    return m_p->getCpuUsePercentage();
}

