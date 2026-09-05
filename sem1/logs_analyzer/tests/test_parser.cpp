#include "parser.hpp"

#include <iostream>
#include <string>

bool test_valid_line() {
    const std::string line =
        "192.168.1.10 GET /api/users 200";

    LogEntry entry;

    if (!parse_line(line, entry)) {
        return false;
    }

    return entry.ip == "192.168.1.10"
        && entry.method == "GET"
        && entry.path == "/api/users"
        && entry.status_code == 200;
}

bool test_another_valid_line() {
    const std::string line =
        "10.0.0.5 POST /api/users 201";

    LogEntry entry;

    if (!parse_line(line, entry)) {
        return false;
    }

    return entry.ip == "10.0.0.5"
        && entry.method == "POST"
        && entry.path == "/api/users"
        && entry.status_code == 201;
}


bool test_invalid_line() {
    const std::string line =
        "this is not a valid log line";

    LogEntry entry;

    return !parse_line(line, entry);
}


int main() {
    if (!test_valid_line()) {
        std::cerr << "test_valid_line FAILED\n";
        return 1;
    }

    if (!test_another_valid_line()) {
        std::cerr << "test_another_valid_line FAILED\n";
        return 1;
    }

    if (!test_invalid_line()) {
        std::cerr << "test_invalid_line FAILED\n";
        return 1;
    }

    std::cout << "All tests passed\n";
    return 0;
}