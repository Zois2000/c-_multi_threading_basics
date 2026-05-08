#pragma once

#include "Cpu.h"
#include "HttpClient.h"
#include <vector>

class WikidataCpuRepository {
public:
    explicit WikidataCpuRepository(const HttpClient& http_client);

    std::vector<Cpu> find_cpus_with_atLeast_threads(int minimum_threads) const;

private:
    const HttpClient& httpClient;

    std::string build_cpu_thread_query(int minimum_threads) const;
};