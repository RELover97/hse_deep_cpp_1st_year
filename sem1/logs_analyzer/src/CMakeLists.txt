add_library(logs_analyzer_core
    parser.cpp
    stats.cpp
)

target_include_directories(logs_analyzer_core PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../include)