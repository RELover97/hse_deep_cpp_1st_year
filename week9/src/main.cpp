#include <iostream>
#include <string>
#include <vector>

// Проверяем, приглашён ли человек: ищем имя среди имён
bool isInvited(const std::vector<std::string>& guests,
               const std::string& name) 
{
    for (const std::string& guest : guests) {
        if (guest == name) {
            return true;
        }
    }
    return false;
}


// Проверяем, занят ли номер места: алгоритм почти такой же
bool isSeatTaken(const std::vector<int>& seats, int seat) 
{
    for (int occupied : seats) {
        if (occupied == seat) {
            return true;
        }
    }
    return false;
}


int main() 
{
    const std::vector<std::string> guests = {"Аня", "Илья", "Маша"};
    const std::vector<int> occupiedSeats = {2, 5};

    std::cout << "Аня приглашена: " << isInvited(guests, "Аня") << '\n';
    std::cout << "Место 5 занято: " << isSeatTaken(occupiedSeats, 5) << '\n';
    std::cout << "Место 3 занято: " << isSeatTaken(occupiedSeats, 3) << '\n';

    return 0;
}
