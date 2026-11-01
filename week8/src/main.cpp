#include "ticket_queue.hpp"
#include <iostream>


int main() 
{
    TicketQueue actual;
    actual.push(101);
    actual.push(102);

    TicketQueue plan(actual); // глубокое копирование
    plan.push(103);
    plan.push(104);
    std::cout << "plan.front is " << plan.front() << "\n";
    std::cout << "plan.back is " << plan.back() << "\n";
    std::cout << "plan.size is " << plan.size() << std::endl;

    plan = actual; // присваивание: старое содержимое plan должно освободиться
    std::cout << "plan.front is " << plan.front() << "\n";
    std::cout << "plan.back is " << plan.back() << "\n";
    std::cout << "plan.size is " << plan.size() << "\n";
}
