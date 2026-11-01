#pragma once
#include "ticket.hpp"
#include <iostream>
#include <memory>
#include <utility>

class Employee {
    std::unique_ptr<Ticket> current_;

public:
    // Сотрудник становится единственным владельцем переданного талона.
    void accept(std::unique_ptr<Ticket> ticket) {
        // Именованный параметр ticket — lvalue, даже если в него передали rvalue.
        current_ = std::move(ticket);
    }

    void print_current() const {
        if (current_) {
            std::cout << "Сотрудник обслуживает: " << current_->number << '\n';
        }
    }
};
