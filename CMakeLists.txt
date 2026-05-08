cmake_minimum_required(VERSION 3.20)

project(c++_multi_threading_basics)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(CURL REQUIRED)
find_package(nlohmann_json CONFIG REQUIRED)

add_executable(c++_multi_threading_basics
    src/main.cpp
    src/http_client.cpp
    src/cpu_parser.cpp
    src/wikidata_cpu_repository.cpp
)

target_include_directories(c++_multi_threading_basics PRIVATE include)

target_link_libraries(c++_multi_threading_basics
    PRIVATE
        CURL::libcurl
        nlohmann_json::nlohmann_json
)