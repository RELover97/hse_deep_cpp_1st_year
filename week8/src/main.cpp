#include "employee.hpp"
#include "report.hpp"
#include "ticket_queue.hpp"
#include <iostream>
#include <memory>
#include <utility>

int main() 
{
    TicketQueue line;
    line.push(std::make_unique<Ticket>(101, "Аня"));
    Employee employee;
    employee.accept(line.take_next());
    employee.print_current();

    DailyReport report = build_report();
    std::cout << "Отчёт " << report.window_name << ": "
              << report.served.size() << " талона(ов)\n";
    DailyReport closed = empty_report();
    std::cout << closed.window_name << ": " << closed.served.size() << '\n';
}
