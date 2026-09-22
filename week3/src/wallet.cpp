#include "wallet.hpp"

#include <iostream>
#include <stdexcept>

// int Wallet::next_id = 1; // definition (until C++17)

/*
    ++next_id:
    next_id = next_id + 1
    return next_id;

    next_id++:
    int previous_next_id = next_id;
    next_id = next_id + 1;
    return previous_next_id;
*/
Wallet::Wallet(int l)
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

Wallet::Wallet(const Wallet& other)
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

Wallet::~Wallet() {
    delete[] history;
}

void Wallet::deposit(int amount) {
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

void Wallet::withdraw(int amount) {
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

int Wallet::get_id() const
{
    return id;
}

int Wallet::get_balance() const
{
    return balance;
}

int Wallet::get_limit() const
{
    return limit;
}

void Wallet::print_history() const {
    for (std::size_t i = 0; i < history_size; ++i) {
        if (history[i].is_deposit) {
            std::cout << '+';
        } else {
            std::cout << '-';
        }

        std::cout << history[i].amount << '\n';
    }
}

void Wallet::inspect() const {
    ++inspection_count;

    std::cout << "Wallet #" << id
                << ": balance = " << balance
                << '\n';
}


// расширение capacity
void Wallet::ensure_capacity(std::size_t required) 
{
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

Wallet& Wallet::operator=(const Wallet& other)
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


int Wallet::get_next_id() {
    return next_id;
}