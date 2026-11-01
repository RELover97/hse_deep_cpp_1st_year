#include "employee.hpp"
#include "ticket_queue.hpp"
#include <iostream>
#include <memory>
#include <utility>

int main() 
{
    TicketQueue line;
    Employee employee;

    auto ticket = std::make_unique<Ticket>(101, "Аня");
    std::cout << "Получен талон №" << ticket->number << '\n';

    // line.push(ticket);         // Ошибка: unique_ptr нельзя копировать.
    line.push(std::move(ticket)); // Владение переходит к очереди.
    std::cout << "После передачи указатель ticket пуст: "
              << std::boolalpha << (ticket == nullptr) << '\n';

    auto next = line.take_next();
    // employee.accept(next);     // Ошибка: next — lvalue.
    employee.accept(std::move(next));  // Владение переходит сотруднику.
    std::cout << "После передачи next пуст: " << (next == nullptr) << '\n';
    employee.print_current();

    // Результаты функций возвращаются по значению (prvalue).
    line.push(std::make_unique<Ticket>(102, "Борис"));
    employee.accept(line.take_next());
    employee.print_current();
}
