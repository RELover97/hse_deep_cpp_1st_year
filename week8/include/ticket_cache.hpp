#pragma once
#include "ticket.hpp"
#include <map>
#include <memory>

// Справочник по номеру: помогает найти живой талон, не удерживая его.
class TicketCache {
    std::map<int, std::weak_ptr<Ticket>> by_number_;

public:
    void remember(const std::shared_ptr<Ticket>& ticket) {
        by_number_[ticket->number] = ticket;
    }

    std::shared_ptr<Ticket> find(int number) {
        auto it = by_number_.find(number);
        if (it == by_number_.end()) {
            return {};
        }
        auto ticket = it->second.lock();
        if (!ticket) {
            by_number_.erase(it);  // Удаляем устаревшую запись при обращении.
        }
        return ticket;
    }
};
