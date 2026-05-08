#pragma

#include "Cpu.h"
#include <string>
#include <vector>

class CpuParser {
    public:
    std::vector<Cpu> parser_cpu_list(const std::string& json_text) const;
};