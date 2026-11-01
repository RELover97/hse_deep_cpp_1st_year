#pragma once

#include "ticket.hpp"
#include <iostream>
#include <memory>
#include <utility>

class Employee {
    std::shared_ptr<Ticket> current_;

public:
    void accept(std::shared_ptr<Ticket> ticket) {
        current_ = std::move(ticket);
        if (current_) {
            current_->status = TicketStatus::serving;
        }
    }

    // Сотрудник отмечает окончание обслуживания и отпускает СВОЮ ссылку.
    void finish() noexcept {
        if (current_) {
            current_->status = TicketStatus::finished;
        }
        current_.reset();
    }

    void print_current() const {
        if (current_) {
            std::cout << "Сотрудник обслуживает талон " << current_->number << '\n';
        } else {
            std::cout << "Сотрудник свободен\n";
        }
    }
};
