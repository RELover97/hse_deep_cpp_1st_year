#pragma once

#include <cstddef> // size_t
#include <iostream>

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
    // Общая реализация умножения для a *= n, a * n и n * a.
    Scores& operator*=(int factor);

    // friend — НЕ метод: свободному operator<< разрешён доступ к private.
    friend std::ostream& operator<<(std::ostream& out, const Scores& scores);

private:

    int values_[3];
};

// Бинарный + создаёт новый объект, используя уже реализованный +=.
Scores operator+(Scores lhs, const Scores& rhs);

// У свободного operator* нет скрытого this; порядок операндов задают параметры.
// Две свободные перегрузки поддерживают оба порядка операндов.
Scores operator*(Scores lhs, int factor);
Scores operator*(int factor, Scores rhs);

// Функтор хранит порог и вызывается через operator().
struct AtLeastTotal {
    int minimum;
    bool operator()(const Scores& scores) const;
};

