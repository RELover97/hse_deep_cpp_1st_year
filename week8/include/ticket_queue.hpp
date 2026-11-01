#pragma once

#include <cstddef>
#include <stdexcept>
#include <utility>

// Очередь выдаёт номера в том порядке, в котором они поступили (FIFO).
// Каждый вызов push создаёт узел в динамической памяти.
class TicketQueue {
    struct Node {
        int number;
        Node* next = nullptr;
    };
    Node* first_ = nullptr;
    Node* last_ = nullptr;
    std::size_t size_ = 0;

public:

    TicketQueue() = default;

    // RAII: при уничтожении очереди удаляем все принадлежащие ей узлы.
    ~TicketQueue() {
        while (!empty()) {
            pop();
        }
    }

    // Глубокое копирование: создаём собственные узлы с теми же номерами, а не копируем указатели
    TicketQueue(const TicketQueue& other) {
        // copy & swap idiom:
        // if creation of copy object thorw exception
        // then current object is not corrupted
        TicketQueue temporary;
        for (Node* node = other.first_; node != nullptr; node = node->next) {
            temporary.push(node->number);
        }
        // must be noexcept
        swap(temporary); // old nodes in copy are destroyed when exiting operator
    }

    TicketQueue& operator=(const TicketQueue& other) {
        // copy & swap idiom:
        // if creation of copy object thorw exception
        // then current object is not corrupted
        TicketQueue copy(other);
        // must be noexcept
        swap(copy);  // old nodes in copy are destroyed when exiting operator
        return *this;
    }

    // Вместо создания новых узлов забираем готовую цепочку.
    TicketQueue(TicketQueue&& other) noexcept
        : first_(other.first_), last_(other.last_), size_(other.size_) {
        other.first_ = nullptr;
        other.last_ = nullptr;
        other.size_ = 0;
    }

    TicketQueue& operator=(TicketQueue&& other) noexcept {
        if (this != &other) {
            TicketQueue empty;
            swap(empty);  // старые узлы будут удалены вместе с empty
            swap(other);  // забираем узлы из other; там остаётся пустота.
        }
        return *this;
    }

    void swap(TicketQueue& other) noexcept {
        // ADL here
        using std::swap;
        swap(first_, other.first_);
        swap(last_, other.last_);
        swap(size_, other.size_);
    }

    void push(int number) {
        Node* node = new Node{number};
        if (last_ != nullptr) {
            last_->next = node;
        } else {
            first_ = node;
        }
        last_ = node;
        ++size_;
    }

    int front() const {
        if (empty()) {
            throw std::logic_error("Очередь пуста");
        }
        return first_->number;
    }

    int back() const {
        if (empty()) {
            throw std::logic_error("Очередь пуста");
        }
        return last_->number;
    }

    void pop() {
        if (empty()) {
            throw std::logic_error("Очередь пуста");
        }
        Node* old = first_;
        first_ = first_->next;
        delete old;  // Каждый new получает соответствующий delete.
        --size_;
        if (first_ == nullptr) {
            last_ = nullptr;
        }
    }

    bool empty() const {
        return first_ == nullptr; 
    }

    std::size_t size() const { 
        return size_; 
    }
};
