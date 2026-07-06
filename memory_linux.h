#ifndef MEMORY_LINUX_H
#define MEMORY_LINUX_H

#include <fstream>
#include <string>
#include <unistd.h>

inline size_t memory_usage() {
    std::ifstream statm("/proc/self/statm");

    long pages = 0;
    long resident = 0;

    statm >> pages >> resident;

    return static_cast<size_t>(resident) * sysconf(_SC_PAGESIZE);
}

#endif