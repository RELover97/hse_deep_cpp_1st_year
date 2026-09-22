#include <iostream>
#include <exception>

class Wallet {
public:
    struct Transaction; // forward declaration

private:

    int id;
    int balance;
    int limit;

    inline static int next_id = 1;

    mutable int inspection_count = 0;

    Transaction* history;
    std::size_t history_size;     // сколько элементов хранится 
    std::size_t history_capacity; // сколько элементов помещается

    // расширение capacity
    void ensure_capacity(std::size_t required) {
        // если требуемой памяти достаточно, то не выделяем новой
        if (required <= history_capacity) {
            return;
        }

        std::size_t new_capacity =
            history_capacity == 0
                ? 4
                : history_capacity * 2;

        // находим ближайшую сверху степень двойки, 
        // которая превосходит запрашиваемую память
        while (new_capacity < required) {
            new_capacity *= 2;
        }

        Transaction* new_history =
            new Transaction[new_capacity];

        // копируем поэлементо историю из старой памяти в новую
        for (std::size_t i = 0; i < history_size; ++i) {
            new_history[i] = history[i];
        }

        delete[] history;

        history = new_history;
        history_capacity = new_capacity;
    }

public:

    struct Transaction {
        int amount;
        bool is_deposit; // true -> add money to wallet, false -> withdraw them
    };

    explicit Wallet(int l)
    : id(next_id++), balance(0), limit(l),
      history(nullptr),
      history_size(0),
      history_capacity(0),
      inspection_count(0)
    {
        if (l <= 0) {
            throw std::invalid_argument("Limit must be positive");
        }
    }

    Wallet(const Wallet& other)
        : id(next_id++),
        balance(other.balance),
        limit(other.limit),
        history(nullptr),
        history_size(other.history_size),
        history_capacity(other.history_capacity),
        inspection_count(0)
    {
        if (history_capacity != 0) {
            history = new Transaction[history_capacity];

            for (std::size_t i = 0; i < history_size; ++i) {
                history[i] = other.history[i];
            }
        }
    }

    Wallet& operator=(const Wallet& other)
    {
        if (this == &other) {
            return *this;
        }

        Transaction* new_history = nullptr;

        if (other.history_capacity != 0) {
            new_history = new Transaction[other.history_capacity];

            for (std::size_t i = 0; i < other.history_size; ++i) {
                new_history[i] = other.history[i];
            }
        }

        delete[] history;

        history = new_history;
        history_size = other.history_size;
        history_capacity = other.history_capacity;

        balance = other.balance;
        limit = other.limit;

        inspection_count = 0;

        return *this;
    }

    ~Wallet() {
        delete[] history;
    }

    void inspect() const {
        ++inspection_count;

        std::cout << "Wallet #" << id
                  << ": balance = " << balance
                  << '\n';
    }

    void deposit(int amount) {
        if (amount <= 0) {
            throw std::invalid_argument("invalid amount");
        }

        if (amount > limit - balance) {
            throw std::invalid_argument("limit exceeded");
        }

        ensure_capacity(history_size + 1);

        balance += amount;

        history[history_size] = {
            amount,
            true
        };

        ++history_size;
    }

    void withdraw(int amount) {
        if (amount <= 0 || amount > balance) {
            std::cout << "Cannot widthdraw as balance is " << balance << std::endl;
            return;
        }

        ensure_capacity(history_size + 1);

        balance -= amount;

        history[history_size] = {
            amount,
            false
        };

        ++history_size;
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

    void print_history() const {
        for (std::size_t i = 0; i < history_size; ++i) {
            if (history[i].is_deposit) {
                std::cout << '+';
            } else {
                std::cout << '-';
            }

            std::cout << history[i].amount << '\n';
        }
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

    w.print_history();

    return 0;
}