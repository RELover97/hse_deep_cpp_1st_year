cmake_minimum_required(VERSION 3.20)

project(LogsAnalyzer VERSION 1.0 LANGUAGES CXX)

add_executable(logs_analyzer
    main.cpp
    src/parser.cpp
    src/stats.cpp
)