#include "employee.hpp"
#include "ticket_queue.hpp"
#include "ticket_registry.hpp"
#include <iostream>
#include <memory>

int main() 
{
    TicketQueue line;
    TicketRegistry registry;
    Employee employee;

    auto ticket = std::make_shared<Ticket>(101, "Аня"); // 1 владелец.
    registry.add(ticket);                             // 2 владельца.
    line.push(std::move(ticket));                    // 2 владельца, не 3.
    auto serving = line.take_next();                 // Очередь отпустила.
    employee.accept(std::move(serving));             // Теперь сотрудник владеет.
    registry.print_status(101);

    // Если завершить обслуживание раньше, реестр всё ещё хранит талон.
    employee.finish();
    registry.print_status(101);                     // Обслужен, но жив.
    registry.erase(101);                            // Последний владелец отпускает.
    // Отдельная shared_owners_demo печатает use_count() после каждой операции.
}
