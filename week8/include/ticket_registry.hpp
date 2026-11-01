#pragma once

#include "ticket.hpp"
#include <iostream>
#include <map>
#include <memory>

// Реестр нужен посетителю для просмотра статуса выданного талона.
// Пока запись существует, реестр самостоятельно владеет объектом Ticket.
class TicketRegistry {
    std::map<int, std::shared_ptr<Ticket>> active_;

public:
    void add(const std::shared_ptr<Ticket>& ticket) {
        active_[ticket->number] = ticket; // Копия shared_ptr, НЕ Ticket.
    }

    void erase(int number) {
        active_.erase(number); // Реестр освобождает только СВОЁ владение.
    }

    std::shared_ptr<Ticket> find(int number) const {
        auto it = active_.find(number);
        if (it == active_.end()) {
            return {};
        }
        return it->second;  // Выдаём временное совместное владение вызывающему.
    }

    void print_status(int number) const {
        auto ticket = find(number);
        if (ticket) {
            std::cout << "Реестр: талон " << number << " — "
                      << ticket->status_text() << '\n';
        } else {
            std::cout << "Реестр: талон " << number << " не зарегистрирован\n";
        }
    }
};
