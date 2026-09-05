#include "include/parser.hpp"
#include "include/stats.hpp"

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#define VERSION 1

int main(int argc, char* argv[]) {

    std::cout << "version is " << VERSION << std::endl;

    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <log-file>\n";
        return 1;
    }

    std::ifstream file(argv[1]);

    if (!file) {
        std::cerr << "Cannot open file: " << argv[1] << '\n';
        return 1;
    }

    std::vector<LogEntry> entries;

    std::string line;

    while (std::getline(file, line)) {
        LogEntry entry;

        if (parse_line(line, entry)) {
            entries.push_back(entry);
        }
    }

    const Statistics statistics = calculate_statistics(entries);

    std::cout << "Total requests: " << statistics.total_requests << '\n';
    std::cout << "Successful:     " << statistics.successful_requests << '\n';
    std::cout << "Errors:         " << statistics.error_requests << '\n';

    return 0;
}