#pragma once
#include "ticket.hpp"
#include <cstddef>
#include <queue>
#include <memory>
#include <stdexcept>
#include <utility>

// Талон является самостоятельным объектом; очередь владеет им единолично.
class TicketQueue {
    std::queue<std::unique_ptr<Ticket>> tickets_;

public:
    void push(std::unique_ptr<Ticket> ticket) {
        tickets_.push(std::move(ticket));
    }

    std::unique_ptr<Ticket> take_next() {
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
