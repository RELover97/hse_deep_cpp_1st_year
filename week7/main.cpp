#include "scores.hpp"
#include <iostream>

int main() {

    Scores first{3, 4, 5};
    std::cout << "Total: " << first.total() << '\n';
}
