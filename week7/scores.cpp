#include "scores.hpp"
#include <ostream>

#include <stdexcept>

Scores::Scores(int a, int b, int c) 
    : values_{a, b, c} 
{}

int Scores::total() const {
    return values_[0] + values_[1] + values_[2];
}

int& Scores::operator[](size_t index) {
    if (index > 2) {
        throw std::out_of_range("Index for scores must be < 3");
    }
    return values_[index];
}

// Возвращаем const&, чтобы нельзя было изменить const Scores.   
const int& Scores::operator[](size_t index) const {
    if (index > 2) {
        throw std::out_of_range("Index for scores must be < 3");
    }
    return values_[index];
}

Scores& Scores::operator+=(const Scores& rhs) {
    // Один цикл реализует саму операцию сложения; + вызовет +=.
    for (size_t i = 0; i < 3; ++i) {
        values_[i] += rhs.values_[i];
    }
    return *this;
}

Scores operator+(Scores lhs, const Scores& rhs) {
    // lhs — локальная копия; исходные аргументы не меняются.
    lhs += rhs;
    return lhs;
}

Scores& Scores::operator*=(int factor) {
    // Применяем множитель ко всем трём результатам.
    for (int& value : values_) {
        value *= factor;
    }
    return *this;
}

Scores operator*(Scores lhs, int factor) {
    lhs *= factor;
    return lhs;
}

Scores operator*(int factor, Scores rhs) {
    // 2 * scores нельзя реализовать методом класса Scores: слева int.
    rhs *= factor;
    return rhs;
}

std::ostream& operator<<(std::ostream& out, const Scores& scores) {
    // Возвращаем тот же поток, чтобы работало out << first << second.
    return out << '[' << scores.values_[0] << ", " << scores.values_[1]
               << ", " << scores.values_[2] << ']';
}

bool AtLeastTotal::operator()(const Scores& scores) const {
    // const: проверка не изменяет ни порог, ни результаты.
    return scores.total() >= minimum;
}

