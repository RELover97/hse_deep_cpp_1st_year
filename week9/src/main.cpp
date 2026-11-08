#include <iostream>
#include <string>
#include <vector>

#include "algorithms.hpp"


int main() 
{
    const std::vector<std::string> guests = {"Аня", "Илья", "Маша"};
    const std::vector<int> occupiedSeats = {2, 5};

    // Из одного описания contains компилятор получает две функции
    std::cout << "Аня приглашена: "
              << contains(guests, std::string("Аня")) << '\n';
    std::cout << "Место 5 занято: " << contains(occupiedSeats, 5) << '\n';

    // Небольшие самостоятельные примеры классических шаблонов
    const int latestSeat = maximum(2, 5);
    int firstSeat = 2;
    int secondSeat = 5;

    swapValues(firstSeat, secondSeat);

    std::cout << "Наибольший номер: " << latestSeat << '\n';
    std::cout << "После обмена: " << firstSeat << ", " << secondSeat << '\n';

    std::string a = "abc";
    std::string b = "def";
    std::cout << "Before swap: a = " << a << ", b = " << b << std::endl;
    swapValues(a, b);
    std::cout << "After swap: a = " << a << ", b = " << b << std::endl;

    return 0;
}
