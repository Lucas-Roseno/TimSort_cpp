// src/MemoryMonitor.cpp
#include "MemoryMonitor.h"
#include <fstream>
#include <string>
#include <iostream>
#include <unistd.h> // For sysconf

namespace MemoryMonitor {
    long getCurrentRSS() {
        long rss = 0L;
        std::ifstream ifs("/proc/self/statm");
        if (ifs.is_open()) {
            long size, resident, share, text, lib, data, dt;
            if (ifs >> size >> resident >> share >> text >> lib >> data >> dt) {
                rss = resident * sysconf(_SC_PAGESIZE) / 1024; // in KB
            }
            ifs.close();
        }
        return rss;
    }
}


