#include "desk.hpp"
#include <iostream>
#include <memory>

int main() {
    std::cout << "Создаём окно и талон\n";
    {
        auto desk = std::make_shared<Desk>();
        auto ticket = std::make_shared<DeskTicket>(101);
        desk->accept(ticket);
        ticket->assigned_desk = desk;
        if (auto assigned = ticket->assigned_desk.lock()) {
            std::cout << "Назначенное окно доступно\n";
        }
    }
    // Слабая обратная ссылка не удерживает окно, оба деструктора вызываются.
    std::cout << "Теперь объекты освобождены\n";
}
