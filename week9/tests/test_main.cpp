#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "algorithms.hpp"
#include "index.hpp"
#include "printer.hpp"

// Простейшая проверка без стороннего тестового фреймворка.
bool expect(bool condition, const std::string& description) {
    if (!condition) {
        std::cerr << "FAIL: " << description << '\n';
    }
    return condition;
}

int main() {
    // Один и тот же шаблон функции используется с разными типами.
    const std::vector<std::string> guests = {"Аня", "Илья"};
    const std::vector<int> seats = {2, 5};
    if (!expect(contains(guests, std::string("Аня")), "find name") ||
        !expect(!contains(guests, std::string("Маша")), "missing name") ||
        !expect(contains(seats, 5), "find seat") ||
        !expect(maximum(2, 5) == 5, "maximum")) {
        return 1;
    }

    int first = 2;
    int second = 5;
    swapValues(first, second);
    if (!expect(first == 5 && second == 2, "swapValues changes originals")) {
        return 1;
    }

    // Ключ может быть строкой, а значение — числом.
    Index<std::string, int, 2> byGuest;
    int foundSeat = -1;
    if (!expect(byGuest.size() == 0, "initially empty") ||
        !expect(byGuest.add("Аня", 2), "add first") ||
        !expect(byGuest.add("Илья", 5), "add second") ||
        !expect(byGuest.size() == 2, "size after two additions") ||
        !expect(byGuest.get("Аня", foundSeat) && foundSeat == 2,
                "get existing key") ||
        !expect(!byGuest.add("Аня", 6), "reject duplicate key") ||
        !expect(!byGuest.add("Маша", 1), "reject when capacity is full") ||
        !expect(byGuest.size() == 2, "rejected inserts do not change size") ||
        !expect(!byGuest.get("Маша", foundSeat), "missing key")) {
        return 1;
    }

    // Те же методы с ключом-числом и строковым значением.
    Index<int, std::string, 2> bySeat;
    std::string foundGuest;
    if (!expect(bySeat.add(2, "Аня"), "reverse add") ||
        !expect(bySeat.get(2, foundGuest) && foundGuest == "Аня",
                "reverse get")) {
        return 1;
    }

    // NTTP входит в тип: при Capacity=1 нельзя добавить две записи.
    Index<std::string, bool, 1> confirmation;
    bool confirmed = false;
    if (!expect(confirmation.add("Аня", true), "add confirmation") ||
        !expect(confirmation.get("Аня", confirmed) && confirmed,
                "read bool value") ||
        !expect(!confirmation.add("Илья", false), "one-element limit")) {
        return 1;
    }

    std::ostringstream out;
    Printer<bool>::print(out, true);
    if (!expect(out.str() == "да", "full specialization for bool")) {
        return 1;
    }

    out.str("");
    out.clear();
    Printer<std::vector<int>>::print(out, seats);
    if (!expect(out.str() == "[2, 5]", "partial specialization for int vector")) {
        return 1;
    }

    out.str("");
    out.clear();
    Printer<std::vector<std::string>>::print(out, guests);
    if (!expect(out.str() == "[Аня, Илья]",
                "partial specialization for string vector")) {
        return 1;
    }

    std::cout << "All checks passed\n";
}
