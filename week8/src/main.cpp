#include "board.hpp"
#include "employee.hpp"
#include "ticket_cache.hpp"
#include "ticket_queue.hpp"
#include "ticket_registry.hpp"
#include <iostream>
#include <memory>

int main() 
{
    TicketQueue line;
    TicketRegistry registry;
    Employee employee;
    Board board;
    TicketCache cache;

    auto ticket = std::make_shared<Ticket>(101, "Аня");
    registry.add(ticket);       // Сильное владение: реестр хранит талон.
    line.push(ticket);          // Сильное владение: очередь хранит талон.
    board.show(ticket);         // Слабая ссылка: табло лишь наблюдает.
    cache.remember(ticket);     // Слабая ссылка: справочник лишь ищет.

    auto serving = line.take_next();
    employee.accept(std::move(serving));
    ticket.reset();             // Локальная переменная больше не владелец.
    board.print();              // Талон ещё жив у реестра и сотрудника.

    employee.finish();         // Сотрудник закончил, но реестр пока владеет.
    registry.print_status(101);
    board.print();              // Ещё жив.
    registry.erase(101);        // Последний сильный владелец исчез.
    board.print();              // Слабая ссылка больше не ведёт к объекту.
    std::cout << "Поиск по номеру: "
              << (cache.find(101) ? "найден" : "объект уже удалён") << '\n';
}
