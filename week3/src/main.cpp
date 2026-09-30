#include <iostream>
#include <exception>

#include "wallet.hpp"

#include <fmt/format.h>

#define SQUARE(x) ((x) * (x))

inline int square(int x)
{
    return x * x;
}

int fun1(int a)
{
    return a;
}

int fun1(int a, int b)
{
    return a + b;
}

int global_var = 1;

static int static_global_var = 1;


int main() 
{
    fmt::print("Hello from main\n");

    int a = square(5);

    int b = SQUARE(6);
    // int c = ((a + 1) * (a + 1)); // 2 * a + 1

    Wallet w(100);
    std::cout << "next id is " << Wallet::get_next_id() << std::endl;
 
    w.deposit(30);
    w.deposit(50);
    w.deposit(50); // warning

    w.withdraw(40);
    w.withdraw(50); // warning

    std::cout << w.get_id() << std::endl;
    std::cout << w.get_balance() << std::endl;
    std::cout << w.get_limit() << std::endl;

    const Wallet w2(500);
    std::cout << "next id is " << Wallet::get_next_id() << std::endl;

    // w2.deposit(30);
    w2.get_limit();

    Wallet w3(w);
    Wallet w4(Wallet(200));

    std::cout << "next id is " <<  Wallet::get_next_id() << std::endl;
    std::cout << w3.get_id() << std::endl;
    std::cout << w3.get_balance() << std::endl;
    std::cout << w3.get_limit() << std::endl;

    w.print_history();

    return 0;
}