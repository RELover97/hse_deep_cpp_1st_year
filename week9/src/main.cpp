#include <iostream>
#include <string>

#include "index.hpp"
#include "printer.hpp"

int main() {
    Index<std::string, int> seatsByGuest;
    Index<int, std::string> guestsBySeat;
    Index<std::string, bool> confirmations;

    seatsByGuest.add("Аня", 2);
    guestsBySeat.add(2, "Аня");
    confirmations.add("Аня", true);

    seatsByGuest.add("Илья", 5);
    guestsBySeat.add(5, "Илья");
    confirmations.add("Илья", false);

    int seat = 0;
    bool confirmed = false;
    if (seatsByGuest.get("Аня", seat) &&
        confirmations.get("Аня", confirmed)) {
        std::cout << "Аня: место ";
        Printer<int>::print(std::cout, seat);
        std::cout << ", подтвердил(а): ";
        Printer<bool>::print(std::cout, confirmed);
        std::cout << '\n';
    }

    return 0;
}
