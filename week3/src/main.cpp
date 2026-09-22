#include "wallet.hpp"

#include <iostream>

int main()
{
    Wallet a(1000);

    a.deposit(300);
    a.withdraw(100);
    a.deposit(500);

    a.inspect();

    std::cout << "History:\n";
    a.print_history();

    Wallet b = a;

    std::cout
        << "Copied wallet id: "
        << b.id()
        << '\n';

    return 0;
}