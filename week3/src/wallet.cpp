#include "wallet.hpp"

#include <iostream>
#include <stdexcept>

Wallet::Wallet(int limit)
    : id_(next_id_++),
      balance_(0),
      limit_(limit),
      history_(nullptr),
      history_size_(0),
      history_capacity_(0),
      inspection_count_(0)
{
    if (limit_ <= 0) {
        throw std::invalid_argument("limit must be positive");
    }
}

Wallet::Wallet(const Wallet& other)
    : id_(next_id_++),
      balance_(other.balance_),
      limit_(other.limit_),
      history_(nullptr),
      history_size_(other.history_size_),
      history_capacity_(other.history_capacity_),
      inspection_count_(0)
{
    if (history_capacity_ != 0) {
        history_ = new Transaction[history_capacity_];

        for (std::size_t i = 0; i < history_size_; ++i) {
            history_[i] = other.history_[i];
        }
    }
}

Wallet::~Wallet()
{
    delete[] history_;
}

void Wallet::ensure_capacity(std::size_t required)
{
    if (required <= history_capacity_) {
        return;
    }

    std::size_t new_capacity =
        history_capacity_ == 0
            ? 4
            : history_capacity_ * 2;

    while (new_capacity < required) {
        new_capacity *= 2;
    }

    Transaction* new_history =
        new Transaction[new_capacity];

    for (std::size_t i = 0; i < history_size_; ++i) {
        new_history[i] = history_[i];
    }

    delete[] history_;

    history_ = new_history;
    history_capacity_ = new_capacity;
}

void Wallet::deposit(int amount)
{
    if (amount <= 0) {
        throw std::invalid_argument("amount must be positive");
    }

    if (amount > limit_ - balance_) {
        throw std::invalid_argument("wallet limit exceeded");
    }

    ensure_capacity(history_size_ + 1);

    balance_ += amount;

    history_[history_size_] = {
        amount,
        true
    };

    ++history_size_;
}

bool Wallet::withdraw(int amount)
{
    if (amount <= 0 || amount > balance_) {
        return false;
    }

    ensure_capacity(history_size_ + 1);

    balance_ -= amount;

    history_[history_size_] = {
        amount,
        false
    };

    ++history_size_;

    return true;
}

int Wallet::id() const
{
    return id_;
}

int Wallet::balance() const
{
    return balance_;
}

int Wallet::limit() const
{
    return limit_;
}

void Wallet::print_history() const
{
    for (std::size_t i = 0; i < history_size_; ++i) {
        std::cout
            << (history_[i].is_deposit ? '+' : '-')
            << history_[i].amount
            << '\n';
    }
}

void Wallet::inspect() const
{
    ++inspection_count_;

    std::cout
        << "Wallet #" << id_
        << ": balance = " << balance_
        << ", limit = " << limit_
        << '\n';
}