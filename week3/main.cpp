#include <iostream>
#include <exception>

class Wallet {
    int id;
    int balance;
    int limit;

public:

    explicit Wallet(int l)
    : id(1), balance(0), limit(l)
    {
        if (l <= 0) {
            throw std::invalid_argument("Limit must be positive");
        }
    }

    void deposit(int amount);

    void withdraw(int amount);
    // getters / геттеры
    int id();
    int balance();
    int limit();
};

int main() 
{
    // Wallet w1;

    Wallet w(1000);
    // Wallet w2 = 3000;

    return 0;
}