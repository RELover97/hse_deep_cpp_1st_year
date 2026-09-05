#include "../include/parser.hpp"

#include <sstream>

bool parse_line(const std::string& line, LogEntry& entry) {
    std::istringstream stream(line);

    return static_cast<bool>(
        stream >> entry.ip
               >> entry.method
               >> entry.path
               >> entry.status_code
    );
}