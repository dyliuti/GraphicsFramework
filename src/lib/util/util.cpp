#include "util.h"

#if defined Q_OS_WIN
#include <AclAPI.h>
#define _WINSOCKAPI_
#include "shellapi.h"
#include <psapi.h>
#include <windows.h>
#pragma comment(lib, "Shell32.lib")
#pragma comment(lib, "Advapi32.lib")
#define AllocMem(x) (HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, x))
#define FreeMem(x) (HeapFree(GetProcessHeap(), HEAP_ZERO_MEMORY, x))
typedef void(WINAPI* PGNSI)(LPSYSTEM_INFO);
#endif

#include <QApplication>
bool Util::processExist(unsigned long processID, const std::wstring& processName)
{
#ifdef Q_OS_WIN
    TCHAR szProcessName[MAX_PATH] = TEXT("<unknown>");
    HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, processID);
    if (NULL != hProcess) {
        HMODULE hMod;
        DWORD cbNeeded;

        if (EnumProcessModules(hProcess, &hMod, sizeof(hMod), &cbNeeded)) {
            GetModuleBaseName(hProcess, hMod, szProcessName, sizeof(szProcessName) / sizeof(TCHAR));
        }
    }
    CloseHandle(hProcess);
    return processName == szProcessName;
#else
    Q_UNUSED(processID)
    Q_UNUSED(processName)
    return false;
#endif
}

QString Util::getAppVersion()
{
    return QApplication::applicationVersion();
}
