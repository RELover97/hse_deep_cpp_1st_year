#include <iostream>

struct Wallet {
    int id;
    int balance;
    int limit;
};

int main() 
{
    Wallet w;

    w.balance = -100;
    w.limit = -400;

    return 0;
}