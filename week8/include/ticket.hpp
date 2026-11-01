#pragma once

#include <string>
#include <utility>
#include <iostream>

enum class TicketStatus { waiting, serving, finished };

struct Ticket {
    int number;
    std::string visitor;
    TicketStatus status = TicketStatus::waiting;

    Ticket(int number, std::string visitor)
        : number(number), visitor(std::move(visitor)) {}

    const char* status_text() const {
        switch (status) {
            case TicketStatus::waiting: return "ожидает";
            case TicketStatus::serving: return "обслуживается";
            case TicketStatus::finished: return "обслужен";
        }
        return "неизвестен";
    }
};
