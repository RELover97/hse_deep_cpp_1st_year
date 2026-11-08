#include <iostream>
#include <string>
#include <vector>

#include "index.hpp"
#include "printer.hpp"

int main() {
    // Число мест известно до запуска программы.
    constexpr std::size_t tableCapacity = 6;
    Index<std::string, int, tableCapacity> seatsByGuest;
    Index<int, std::string, tableCapacity> guestsBySeat;
    Index<std::string, bool, tableCapacity> confirmations;

    seatsByGuest.add("Аня", 2);
    guestsBySeat.add(2, "Аня");
    confirmations.add("Аня", true);

    seatsByGuest.add("Илья", 5);
    guestsBySeat.add(5, "Илья");
    confirmations.add("Илья", false);

    const std::vector<std::string> names = {"Аня", "Илья"};
    const std::vector<int> occupiedSeats = {2, 5};
    std::cout << "Гости: ";
    Printer<std::vector<std::string>>::print(std::cout, names);
    std::cout << "\nЗанятые места: ";
    Printer<std::vector<int>>::print(std::cout, occupiedSeats);
    std::cout << '\n';

    bool confirmed = false;
    if (confirmations.get("Аня", confirmed)) {
        std::cout << "Аня подтвердила: ";
        Printer<bool>::print(std::cout, confirmed);
        std::cout << '\n';
    }

    return 0;
}
