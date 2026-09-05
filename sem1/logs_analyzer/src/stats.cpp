#include "../include/stats.hpp"

Statistics calculate_statistics(const std::vector<LogEntry>& entries) {
    Statistics result;

    result.total_requests = entries.size();

    for (const auto& entry : entries) {
        if (entry.status_code >= 200 && entry.status_code < 400) {
            ++result.successful_requests;
        } else if (entry.status_code >= 400) {
            ++result.error_requests;
        }
    }

    return result;
}