#include <iostream>
#include <exception>

#define SQUARE(x) ((x) * (x))

inline int square(int x)
{
    return x * x;
}


class Wallet {
    int id;
    int balance;
    int limit;

    inline static int next_id = 1; // declaration + definition (since C++17)

public:

    /*
        ++next_id:
        next_id = next_id + 1
        return next_id;

        next_id++:
        int previous_next_id = next_id;
        next_id = next_id + 1;
        return previous_next_id;
    */

    explicit Wallet(int l)
    : id(next_id++), balance(0), limit(l)
    {
        if (l <= 0) {
            throw std::invalid_argument("Limit must be positive");
        }
    }

    Wallet(const Wallet &other) {
        balance = other.balance;
        limit = other.limit;
        id = other.id;
    }

    ~Wallet() = default;

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
    int get_id() const {
        return id;
    }

    int get_balance() const {
        return balance;
    }

    int get_limit() const {
        return limit;
    }

    static int get_next_id() {
        return next_id;
    }
};

// int Wallet::next_id = 1; // definition (until C++17)


int main() 
{
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

    return 0;
}