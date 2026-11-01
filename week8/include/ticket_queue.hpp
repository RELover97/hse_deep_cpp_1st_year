#pragma once
#include "ticket.hpp"
#include <cstddef>
#include <queue>
#include <memory>
#include <stdexcept>
#include <utility>

class TicketQueue {
    std::queue<std::shared_ptr<Ticket>> tickets_;

public:
    void push(std::shared_ptr<Ticket> ticket) {
        tickets_.push(std::move(ticket));
    }

    std::shared_ptr<Ticket> take_next() {
        if (tickets_.empty()) {
            throw std::logic_error("Очередь пуста");
        }
        auto ticket = std::move(tickets_.front());
        tickets_.pop();
        return ticket;
    }

    bool empty() const { 
        return tickets_.empty(); 
    }

    std::size_t size() const { 
        return tickets_.size(); 
    }
};
