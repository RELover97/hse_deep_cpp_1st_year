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
    }
    // Намеренно неправильный пример: оба счётчика остаются ненулевыми.
    // Деструкторы НЕ вызовутся, хотя локальные переменные исчезли.
    std::cout << "Область видимости закончилась, но деструкторы не вызвались\n";
}
