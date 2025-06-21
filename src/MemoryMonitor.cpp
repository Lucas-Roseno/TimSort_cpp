// src/MemoryMonitor.cpp
#include "MemoryMonitor.h"
#include <fstream>
#include <string>
#include <iostream>
#include <unistd.h> // For sysconf
#include <sys/resource.h>

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

    long getMaxRSS() {
        struct rusage usage;
        // Pede ao sistema operacional as estatísticas de uso de recursos para o próprio processo
        if (getrusage(RUSAGE_SELF, &usage) == 0) {
            // Em Linux, o valor de ru_maxrss já é fornecido em kilobytes.
            return usage.ru_maxrss;
        } else {
            // Em caso de erro, retorna 0 ou trata o erro como preferir.
            perror("getrusage");
            return 0;
        }
    }
}


