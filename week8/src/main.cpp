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

    // У нового талона есть два независимых назначения:
    // очередь на обслуживание и реестр для проверки статуса.
    auto ticket = std::make_shared<Ticket>(101, "Аня");
    registry.add(ticket);
    line.push(std::move(ticket)); // Переместили локальный shared_ptr в очередь.

    registry.print_status(101);    // Ожидает.
    employee.accept(line.take_next());
    registry.print_status(101);    // Обслуживается: объект всё тот же.

    // Сессию посетителя на терминале завершили, но сотрудник продолжает работу.
    registry.erase(101);
    employee.print_current();     // Объект ещё существует.
    employee.finish();           // Последний владелец отпускает объект.
}
