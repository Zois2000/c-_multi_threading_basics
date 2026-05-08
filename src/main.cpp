#include "HttpClient.h"
#include "WikidataCpuRepository.h"

#include <iostream>
#include <vector>

int main() {
    try {
        // Mindestanzahl gewünschter CPU-Threads
        int minimumThreads = 16;

        // HTTP-Modul erstellen
        HttpClient httpClient;

        // Repository für CPU-Daten erstellen
        WikidataCpuRepository cpuRepository(httpClient);

        // CPUs von Wikidata laden
        std::vector<Cpu> cpus =
            cpuRepository.find_cpus_with_atLeast_threads(minimumThreads);

        // Ergebnis ausgeben
        std::cout << "CPUs mit mindestens "
                  << minimumThreads
                  << " Threads:\n\n";

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