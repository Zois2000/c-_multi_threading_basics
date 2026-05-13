#include "WikidataCpuRepository.h"
#include "CpuParser.h"
#include <map>
#include <sstream>

WikidataCpuRepository::WikidataCpuRepository(const HttpClient& http_client)
    : http_client(http_client) {
}

// Baut die SPARQL-Query dynamisch
std::string WikidataCpuRepository::build_cpu_thread_query() const 
{
    std::ostringstream query;

    query << R"(
    SELECT ?cpu ?cpuLabel ?cores ?threads WHERE {
        ?cpu wdt:P7443 ?threads.
        OPTIONAL { ?cpu wdt:P1141 ?cores. }
    SERVICE wikibase:label {
        bd:serviceParam wikibase:language "en".
        }
    }
    ORDER BY DESC(?threads)
    LIMIT 1
    )";

    return query.str();
}

std::vector<Cpu> WikidataCpuRepository::find_cpu_with_max_threads() const 
{
    std::string query = build_cpu_thread_query();

    std::map<std::string, std::string> formFields = {
        {"query", query},
        {"format", "json"}
    };

    std::string jsonText = http_client.post_form(
        "https://query.wikidata.org/sparql",
        formFields
    );

    CpuParser parser;
    return parser.parser_cpu_list(jsonText);
}