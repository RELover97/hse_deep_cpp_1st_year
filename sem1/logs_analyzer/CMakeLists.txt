cmake_minimum_required(VERSION 3.20)

project(LogsAnalyzer VERSION 1.0 LANGUAGES CXX)

add_executable(logs_analyzer
    main.cpp
    src/parser.cpp
    src/stats.cpp
)

add_library(logs_analyzer_core
    src/parser.cpp
    src/stats.cpp
)

target_link_libraries(logs_analyzer PRIVATE logs_analyzer_core)