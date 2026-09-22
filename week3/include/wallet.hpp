#pragma once

#include <cstddef>

class Wallet {
public:
    struct Transaction; // forward declaration

private:

    int id;
    int balance;
    int limit;

    inline static int next_id = 1; // declaration + definition (since C++17)

    mutable int inspection_count = 0;

    Transaction* history;
    std::size_t history_size;     // сколько элементов хранится 
    std::size_t history_capacity; // сколько элементов помещается

    // расширение capacity
    void ensure_capacity(std::size_t required);

public:

    struct Transaction {
        int amount;
        bool is_deposit; // true -> add money to wallet, false -> withdraw them
    };

    explicit Wallet(int l);

    Wallet(const Wallet& other);

    Wallet& operator=(const Wallet& other);

    ~Wallet();

    void inspect() const;

    void deposit(int amount);

    void withdraw(int amount);

    // getters / геттеры

    int get_id() const;

    int get_balance() const;

    int get_limit() const;

    void print_history() const;

    static int get_next_id();
};