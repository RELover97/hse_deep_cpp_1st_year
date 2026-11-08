#include <iostream>
#include <string>

#include "index.hpp"

int main() {
    // Одна конкретная специализация Index.
    Index<std::string, int, 16> seats;
    seats.add("Аня", 2);
    int place = 0;
    if (seats.get("Аня", place)) {
        std::cout << place << '\n';
    }
}
