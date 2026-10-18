#include "scores.hpp"
#include <iostream>


namespace {
// Одно имя print, разные типы параметров: выбор делает компилятор.
void print(int value) {
    std::cout << "print(int): " << value << '\n';
}
void print(double value) {
    std::cout << "print(double): " << value << '\n';
}
void print(const Scores& value) {
    std::cout << "print(Scores): total " << value.total() << '\n';
}
}


namespace {
// Оба преобразования int -> long и int -> double имеют одинаковый ранг.
void choose(long) {
    std::cout << "choose(long)\n";
}
void choose(double) {
    std::cout << "choose(double)\n";
}
}

int main() {

    Scores first{3, 4, 5};
    std::cout << "Total: " << first.total() << '\n';

    print(7);
    print(2.5);
    print(first);

    short small = 6;
    float fraction = 2.5f;
    print(small);     // print(int): promotion
    print(fraction);  // print(double): promotion

    // choose(42);  // Не компилируется: нет лучшей перегрузки.
    // Явный static_cast снимает неоднозначность.
    choose(static_cast<long>(42));
    choose(static_cast<double>(42));
}
