#pragma once

#include <cstddef>
#include <stdexcept>

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
