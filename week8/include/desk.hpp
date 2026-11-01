#pragma once
#include <iostream>
#include <memory>

class Desk;

struct DeskTicket {
    int number;
    std::weak_ptr<Desk> assigned_desk;  // Талон знает окно, но не владеет им.
    explicit DeskTicket(int number) : number(number) {}
    ~DeskTicket() { std::cout << "Удалён талон " << number << '\n'; }
};

class Desk {
    std::shared_ptr<DeskTicket> current_;

public:
    ~Desk() { std::cout << "Удалено окно\n"; }

    void accept(const std::shared_ptr<DeskTicket>& ticket) {
        current_ = ticket;
    }
};
