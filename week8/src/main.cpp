#include "ticket_queue.hpp"
#include <iostream>
#include <utility>

int main() 
{
    TicketQueue window_a;
    window_a.push(101);
    window_a.push(102);

    // Окно A закрывается; передаём всю очередь окну B без копии узлов
    // std::move(window_a) — "разрешаем" перемещение.
    TicketQueue window_b = std::move(window_a);
    std::cout << "A после передачи: " << window_a.size() << '\n';
    std::cout << "B после передачи: " << window_b.size() << '\n';

    TicketQueue window_c;
    window_c.push(900);
    // оператор перемещения освобождает старые узлы окна C
    window_c = std::move(window_b);
    std::cout << "C обслуживает талон: " << window_c.front() << '\n';
}
