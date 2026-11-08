#pragma once

#include <ostream>

// Общий вариант: тип можно вывести оператором <<.
template <typename T>
struct Printer {
    static void print(std::ostream& out, const T& value) {
        out << value;
    }
};

// Для подтверждения участия печатаем понятные слова, а не 1 или 0.
template <>
struct Printer<bool> {
    static void print(std::ostream& out, bool value) {
        out << (value ? "да" : "нет");
    }
};
