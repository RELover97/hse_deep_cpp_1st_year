#include <iostream>
#include <string>

#include "index.hpp"

int main() 
{
    // Один шаблон класса; два разных набора аргументов типа
    Index<std::string, int> seatsByGuest;
    Index<int, std::string> guestsBySeat;

    seatsByGuest.add("Аня", 2);
    guestsBySeat.add(2, "Аня");
    seatsByGuest.add("Илья", 5);
    guestsBySeat.add(5, "Илья");

    int seat = 0;
    std::string guest;
    if (seatsByGuest.get("Аня", seat)) {
        std::cout << "Аня: место " << seat << '\n';
    }
    if (guestsBySeat.get(5, guest)) {
        std::cout << "Место 5: " << guest << '\n';
    }

    return 0;
}
