#pragma once
#include <string>
#include <utility>
#include <iostream>

// У каждого талона есть номер и имя посетителя.
struct Ticket {
    int number;
    std::string visitor;

    Ticket(int number, std::string visitor)
        : number(number), visitor(std::move(visitor)) 
    {
        std::cout << "Ctor: ticket #" << number << " for " << visitor << "\n";
    }

    Ticket(const Ticket&)
    {
        std::cout << "Copy ctor: ticket #" << number << " for " << visitor << "\n";
    }

    Ticket(Ticket&&)
    {
        std::cout << "Move ctor: ticket #" << number << " for " << visitor << "\n";
    }

    ~Ticket()
    {
        std::cout << "Dtor: ticket #" << number << " for " << visitor << "\n";
    }
};
