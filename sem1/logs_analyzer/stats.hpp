#pragma once

#include "parser.hpp"

#include <cstddef>
#include <vector>

struct Statistics {
    std::size_t total_requests = 0;
    std::size_t successful_requests = 0;
    std::size_t error_requests = 0;
};

Statistics calculate_statistics(const std::vector<LogEntry>& entries);