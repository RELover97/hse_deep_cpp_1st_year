#include "ticket_queue.hpp"
#include <iostream>
#include <memory> // std::unique_ptr

int main() 
{
    TicketQueue line;
    line.push(std::make_unique<Ticket>(101, "Аня"));
    line.push(std::make_unique<Ticket>(102, "Борис"));

    // Теперь талоном владеет сотрудник, а не очередь
    std::unique_ptr<Ticket> at_window = line.take_next();
    std::cout << "Обслуживаем: " << at_window->number
              << " (" << at_window->visitor << ")\n";

    std::cout << "Осталось в очереди: " << line.size() << '\n';
}
