#include <iostream>
#include <string>

#include "seat_maps.hpp"

int main() 
{
    SeatsByGuest seats;

    seats.add("Аня", 2);
    seats.add("Илья", 5);
    seats.add("Маша", 1);

    int seat = 0;
    if (seats.get("Илья", seat)) {
        std::cout << "Илья сидит на месте " << seat << '\n';
    }

    if (!seats.get("Оля", seat)) {
        std::cout << "Оля пока не рассажена\n";
    }

    return 0;
}
