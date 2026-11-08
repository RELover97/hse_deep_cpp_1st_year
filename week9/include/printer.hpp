#pragma once

#include <cstddef>
#include <ostream>
#include <vector>

// Общий вариант: выводим тип, для которого определён operator<<.
template <typename T>
struct Printer {
    static void print(std::ostream& out, const T& value) {
        out << value;
    }
};

// Полная специализация: ровно один тип bool.
template <>
struct Printer<bool> {
    static void print(std::ostream& out, bool value) {
        out << (value ? "да" : "нет");
    }
};

// Частичная специализация: любой std::vector<T>, независимо от T
template <typename T>
struct Printer<std::vector<T>> {
    static void print(std::ostream& out, const std::vector<T>& values) {
        out << '[';
        for (std::size_t i = 0; i < values.size(); ++i) {
            if (i != 0) {
                out << ", ";
            }
            // Выбираем формат каждого элемента по его собственному типу
            Printer<T>::print(out, values[i]);
        }
        out << ']';
    }
};
