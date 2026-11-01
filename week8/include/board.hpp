#pragma once
#include "ticket.hpp"
#include <iostream>
#include <memory>

// Табло наблюдает, но не обязано продлевать время жизни талона.
class Board {
    std::weak_ptr<Ticket> visible_;

public:
    void show(const std::shared_ptr<Ticket>& ticket) {
        visible_ = ticket;
    }

    void print() const {
        if (auto ticket = visible_.lock()) {
            std::cout << "Табло показывает: " << ticket->number << '\n';
        } else {
            std::cout << "Талон больше не обслуживается\n";
        }
    }
};
