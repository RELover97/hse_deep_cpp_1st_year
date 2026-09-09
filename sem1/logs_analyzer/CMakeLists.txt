cmake_minimum_required(VERSION 3.20)

project(LogsAnalyzer VERSION 1.0 LANGUAGES CXX)

add_subdirectory(src)
add_subdirectory(tests)

add_executable(logs_analyzer
    main.cpp
)

target_link_libraries(logs_analyzer PRIVATE logs_analyzer_core)