#include <iostream>
#include <exception>

class Wallet {
    int id;
    int balance;
    int limit;

    inline static int next_id = 1;

    mutable int inspection_count = 0;

public:

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

    void inspect() const {
        ++inspection_count;

        std::cout << "Wallet #" << id
                  << ": balance = " << balance
                  << '\n';
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


int main() 
{
    Wallet w(100);
    std::cout << Wallet::get_next_id() << std::endl;
 
    w.deposit(30);
    w.deposit(50);
    w.deposit(50); // warning

    w.withdraw(40);
    w.withdraw(50); // warning

    std::cout << w.get_id() << std::endl;
    std::cout << w.get_balance() << std::endl;
    std::cout << w.get_limit() << std::endl;

    const Wallet w2(500);
    std::cout << Wallet::get_next_id() << std::endl;

    // w2.deposit(30);
    w2.get_limit();

    Wallet w3(w);
    std::cout << Wallet::get_next_id() << std::endl;

    std::cout << w3.get_id() << std::endl;
    std::cout << w3.get_balance() << std::endl;
    std::cout << w3.get_limit() << std::endl;

    return 0;
}