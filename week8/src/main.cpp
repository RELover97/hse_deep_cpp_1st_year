#include "ticket_queue.hpp"
#include <iostream>

int main() 
{
    TicketQueue line;
    line.push(101);
    line.push(102);
    line.push(103);

    std::cout << "Выдано талонов: " << line.size() << '\n';
    std::cout << "Сейчас вызываем: " << line.front() << '\n';
    
    line.pop();
    // Ещё два узла останутся в очереди. Их освободит деструктор line.
    std::cout << "Осталось в очереди: " << line.size() << '\n';
}
