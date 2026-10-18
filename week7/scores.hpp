#pragma once

#include <cstddef> // size_t

class Scores {
public:

    Scores(int a, int b, int c);
    
    int total() const;

    // Неконстантный объект отдаёт изменяемую ссылку: scores[i] = value.
    // operator[] — метод: при вызове first[i] слева неявно передаётся this.
    int& operator[](size_t index);
    // Из const-объекта нельзя получить ссылку, разрешающую изменение.
    const int& operator[](size_t index) const;

    // Меняем *this и возвращаем ссылку на тот же объект.
    // В методе есть неявный параметр this (указатель на левый операнд).
    Scores& operator+=(const Scores& rhs);

private:

    int values_[3];
};

// Бинарный + создаёт новый объект, используя уже реализованный +=.
Scores operator+(Scores lhs, const Scores& rhs);