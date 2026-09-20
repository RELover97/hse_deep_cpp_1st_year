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

    void deposit(int amount) {
        if (balance + amount <= limit) {
            balance += amount;
        } else {
            std::cout << "Trying to exceed limit of " 
                     << limit 
                     << " having balance "
                     << balance
                     << std::endl;
        }
    }

    void withdraw(int amount) {
        if (balance - amount >= 0) {
            balance -= amount;
        } else {
            std::cout << "Trying to withdraw more money " 
                      << " than having on balance: "
                      << balance
                      << std::endl;
        }
    }

    // getters / геттеры
    int get_id() {
        return id;
    }

    int get_balance() {
        return balance;
    }

    int get_limit() {
        return limit;
    }
};


int main() 
{
    // Wallet w1;

    Wallet w(100);
 
    w.deposit(30);
    w.deposit(50);
    w.deposit(50); // warning

    w.withdraw(40);
    w.withdraw(50); // warning

    std::cout << w.get_id() << std::endl;
    std::cout << w.get_balance() << std::endl;
    std::cout << w.get_limit() << std::endl;
<<<<<<< HEAD
=======


    const Wallet w2(500);

    // w2.deposit(30);
    w2.get_limit();
>>>>>>> c6a1e7a (const Wallet)

    return 0;
}