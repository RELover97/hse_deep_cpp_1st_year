#pragma once

#include <string>

struct LogEntry {
    std::string ip;
    std::string method;
    std::string path;
    int status_code;
};

bool parse_line(const std::string& line, LogEntry& entry);