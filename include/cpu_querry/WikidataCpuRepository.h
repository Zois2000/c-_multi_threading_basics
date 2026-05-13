#pragma once

#include "Cpu.h"
#include "HttpClient.h"
#include <vector>

class WikidataCpuRepository {
public:
    explicit WikidataCpuRepository(const HttpClient& http_client);

    std::vector<Cpu> find_cpu_with_max_threads() const;

private:
    const HttpClient& http_client;

    std::string build_cpu_thread_query() const;
};