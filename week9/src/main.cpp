#include <iostream>
#include <string>

#include "seat_maps.hpp"

int main() 
{
    SeatsByGuest seatsByGuest;
    GuestsBySeat guestsBySeat;

    // Проверяем обе стороны, прежде чем добавлять сведения в обе таблицы
    const std::string guest = "Аня";
    const int seat = 2;
    int existingSeat = 0;
    std::string existingGuest;
    if (!seatsByGuest.get(guest, existingSeat) &&
        !guestsBySeat.get(seat, existingGuest)) {
        seatsByGuest.add(guest, seat);
        guestsBySeat.add(seat, guest);
    }

    int foundSeat = 0;
    std::string foundGuest;
    if (seatsByGuest.get("Аня", foundSeat)) {
        std::cout << "Аня: место " << foundSeat << '\n';
    }
    if (guestsBySeat.get(2, foundGuest)) {
        std::cout << "Место 2: " << foundGuest << '\n';
    }

    return 0;
}
