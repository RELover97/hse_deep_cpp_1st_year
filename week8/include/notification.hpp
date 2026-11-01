#pragma once
#include "ticket.hpp"
#include <iostream>
#include <memory>
#include <string>
#include <utility>
#include <vector>

// Общее правило для всех получателей события вызова талона.
class TicketObserver {
public:
    virtual ~TicketObserver() = default;
    virtual void on_called(const Ticket& ticket) = 0;
};

// Конкретный наблюдатель: приложение на телефоне посетителя.
class PhoneNotification : public TicketObserver {
    std::string recipient_;

public:
    explicit PhoneNotification(std::string recipient)
        : recipient_(std::move(recipient)) {}

    void on_called(const Ticket& ticket) override {
        std::cout << "Телефон " << recipient_ << ": талон №" << ticket.number
                  << " приглашается к окну\n";
    }
};

class Notifications {
    // Мы помним подписчиков, но НЕ продлеваем время их жизни.
    std::vector<std::weak_ptr<TicketObserver>> observers_;

public:
    void subscribe(const std::shared_ptr<TicketObserver>& observer) {
        observers_.push_back(observer);
    }

    void announce(const Ticket& ticket) {
        auto it = observers_.begin();
        while (it != observers_.end()) {
            // lock() временно продлевает время жизни реально существующего объекта.
            if (auto observer = it->lock()) {
                observer->on_called(ticket);
                ++it;
            } else {
                // Ссылку на уже уничтоженного подписчика можно убрать.
                it = observers_.erase(it);
            }
        }
    }
};
