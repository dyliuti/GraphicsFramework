#include "systemstatus.h"
#include "private/systemstatus_win.h"

#include <QString>

#include <TlHelp32.h>
#include <process.h>
#include <psapi.h>
#pragma comment(lib, "psapi.lib")

__int64 Filetime2Int64(const FILETIME *ftime)
{
    LARGE_INTEGER li;
    li.LowPart = ftime->dwLowDateTime;
    li.HighPart = ftime->dwHighDateTime;
    return li.QuadPart;
}

__int64 CompareFileTime2(FILETIME preTime, FILETIME nowTime)
{
    return Filetime2Int64(&nowTime) - Filetime2Int64(&preTime);
}

SystemStatusPrivate::SystemStatusPrivate(QObject *parent)
    : SystemStatusBasePrivate(parent)
{
    m_hProcess = OpenProcess(PROCESS_QUERY_INFORMATION, FALSE, m_appId);
}

SystemStatusPrivate::~SystemStatusPrivate()
{
    if (m_hProcess) {
        CloseHandle(m_hProcess);
    }
}

QPair<float, float> SystemStatusPrivate::getCpuInfo()
{
    return getCpuUsePercentage();
}

void SystemStatusPrivate::emitCustomSignal(quint32 memUsed)
{
#if defined(EEO_HASLOG)
    if (m_isFirst && memUsed > 1536) {
        m_isFirst = false;
        emit sigMemUsedOverflow(memUsed);
    }
#endif
}

float SystemStatusPrivate::getSysMemUsePercentage()
{
    MEMORYSTATUSEX memory_status;
    memory_status.dwLength = sizeof(memory_status);
    GlobalMemoryStatusEx(&memory_status);
    return float(memory_status.dwMemoryLoad);
}

float SystemStatusPrivate::getSysTotalMem()
{
    MEMORYSTATUSEX memory_status;
    memory_status.dwLength = sizeof(memory_status);
    GlobalMemoryStatusEx(&memory_status);
    return float(memory_status.ullTotalPhys / (1024 * 1024));
}

qint32 SystemStatusPrivate::getCurProcessMemUsed()
{
    HANDLE handle = GetCurrentProcess();
    PROCESS_MEMORY_COUNTERS_EX pmc = {0};
    if (!GetProcessMemoryInfo(handle, (PROCESS_MEMORY_COUNTERS *) &pmc, sizeof(pmc))) {
        return -1;
    }
    int deno = 1024 * 1024;
    return qint32(pmc.WorkingSetSize / deno);
}

QPair<float, float> SystemStatusPrivate::getCpuUsePercentage()
{
    FILETIME idleTime;
    FILETIME kernelTime;
    FILETIME userTime;

    FILETIME processCreateTime;
    FILETIME processExitExitTime;
    FILETIME processKernelTime;
    FILETIME processUserTime;

    GetSystemTimes(&idleTime, &kernelTime, &userTime);
    GetProcessTimes(m_hProcess,
                    &processCreateTime,
                    &processExitExitTime,
                    &processKernelTime,
                    &processUserTime);

    if (m_isFirstGetData) {
        m_isFirstGetData = false;

        m_preIdleTime = idleTime;
        m_preKernelTime = kernelTime;
        m_preUserTime = userTime;

        m_preProcessKernelTime = processKernelTime;
        m_preProcessUserTime = processUserTime;

        return qMakePair(-1, -1);
    }

    long long idle = CompareFileTime2(m_preIdleTime, idleTime);
    long long kernel = CompareFileTime2(m_preKernelTime, kernelTime);
    long long user = CompareFileTime2(m_preUserTime, userTime);

    long long pKernel = CompareFileTime2(m_preProcessKernelTime, processKernelTime);
    long long pUser = CompareFileTime2(m_preProcessUserTime, processUserTime);

    float totalValue = float(100.0 * (kernel + user - idle) / (kernel + user));
    float processValue = float(100.0 * (pKernel + pUser) / (kernel + user));

    m_preIdleTime = idleTime;
    m_preKernelTime = kernelTime;
    m_preUserTime = userTime;

    m_preProcessKernelTime = processKernelTime;
    m_preProcessUserTime = processUserTime;

    return qMakePair(totalValue, processValue);
}
