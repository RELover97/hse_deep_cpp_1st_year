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

int main() {

    Scores first{3, 4, 5};
    std::cout << "Total: " << first.total() << '\n';

    print(7);
    print(2.5);
    print(first);
}
