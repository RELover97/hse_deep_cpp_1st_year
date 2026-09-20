#include <iostream>

class Wallet {
    int id;
    int balance;
    int limit;

public:

    void deposit(int amount);

    void withdraw(int amount);
    // getters / геттеры
    int id();
    int balance();
    int limit();
};

int main() 
{
    Wallet w;

    return 0;
}