#include "HttpClient.h"
#include "WikidataCpuRepository.h"

#include <iostream>
#include <vector>

int main() {
    try {
        // HTTP-Modul erstellen
        HttpClient httpClient;

        // Repository für CPU-Daten erstellen
        WikidataCpuRepository cpuRepository(httpClient);

        // CPU mit maximaler Thread-Anzahl laden
        std::vector<Cpu> cpus = cpuRepository.find_cpu_with_max_threads();

        // Ergebnis ausgeben
        std::cout << "CPU mit den meisten Threads:\n\n";

        for (const Cpu& cpu : cpus) {
            std::cout << cpu.name
                      << " | Kerne: " << cpu.cores
                      << " | Threads: " << cpu.threads
                      << '\n';
        }
    }
    catch (const std::exception& error) {
        std::cerr << "Fehler: " << error.what() << '\n';
        return 1;
    }

    return 0;
}