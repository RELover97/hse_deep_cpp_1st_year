#pragma once

#include <cstddef>

struct Transaction {
    int amount;
    bool is_deposit;
};

class Wallet {
private:
    const int id_;
    int balance_;
    int limit_;

    Transaction* history_;
    std::size_t history_size_;
    std::size_t history_capacity_;

    mutable std::size_t inspection_count_;

    inline static int next_id_ = 1;

    void ensure_capacity(std::size_t required);

public:

    explicit Wallet(int limit);
    Wallet(const Wallet& other);

    Wallet& operator=(const Wallet&) = delete;

    ~Wallet();

    void deposit(int amount);
    bool withdraw(int amount);

    int id() const;
    int balance() const;
    int limit() const;

    void print_history() const;
    void inspect() const;
};