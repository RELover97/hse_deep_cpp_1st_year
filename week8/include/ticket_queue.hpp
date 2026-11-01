#pragma once

#include <cstddef>
#include <queue>
#include <stdexcept>

// Вместо самодельных узлов памятью управляет стандартный контейнер.
class TicketQueue {
    std::queue<int> numbers_;

public:

    void push(int number) { 
        numbers_.push(number); 
    }

    int front() const {
        if (numbers_.empty()) {
            throw std::logic_error("Очередь пуста");
        }
        return numbers_.front();
    }

    int back() const {
        if (empty()) {
            throw std::logic_error("Очередь пуста");
        }
        return numbers_.back();
    }

    void pop() {
        if (numbers_.empty()) {
            throw std::logic_error("Очередь пуста");
        }
        numbers_.pop();
    }

    bool empty() const {
        return numbers_.size() == 0; 
    }

    std::size_t size() const { 
        return numbers_.size(); 
    }
};
