#include "CpuParser.h"
#include <nlohmann/json.hpp>

using json = nlohmann::json;

std::vector<Cpu> CpuParser::parser_cpu_list(const std::string& jsonText) const {
    std::vector<Cpu> cpus;

    json data = json::parse(jsonText);

    for (const auto& item : data["results"]["bindings"]) {
        Cpu cpu;

        cpu.name = item["cpuLabel"]["value"];
        cpu.threads = item["threads"]["value"];

        if (item.contains("cores")) {
            cpu.cores = item["cores"]["value"];
        } else {
            cpu.cores = "?";
        }

        cpus.push_back(cpu);
    }

    return cpus;
}