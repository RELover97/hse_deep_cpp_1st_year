#pragma once

#include <vector>

// Один алгоритм поиска подходит для любого типа с операцией ==
template <typename T>
bool contains(const std::vector<T>& values, const T& wanted) {
    for (const T& value : values) {
        if (value == wanted) {
            return true;
        }
    }
    return false;
}

// Классическая задача: максимальный из двух объектов сравнимого типа
template <typename T>
T maximum(T first, T second) {
    return first < second ? second : first;
}

// Классическая задача: обмен двух объектов одного типа.
// Для повседневного кода обычно достаточно std::swap.
template <typename T>
void swapValues(T& first, T& second) {
    T temporary = first;
    first = second;
    second = temporary;
}
