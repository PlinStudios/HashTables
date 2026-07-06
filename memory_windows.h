#ifndef MEMORY_WINDOWS_H
#define MEMORY_WINDOWS_H

#include <windows.h>
#include <psapi.h>

#pragma comment(lib, "psapi.lib")

inline size_t memory_usage() {
    PROCESS_MEMORY_COUNTERS_EX pmc;

    if (GetProcessMemoryInfo(
            GetCurrentProcess(),
            (PROCESS_MEMORY_COUNTERS*)&pmc,
            sizeof(pmc)))
    {
        return static_cast<size_t>(pmc.WorkingSetSize);
    }

    return 0;
}

#endif