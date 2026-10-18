#include "scores.hpp"
#include "student_id.hpp"
#include <algorithm>
#include <iostream>
#include <map>
#include <vector>


namespace {
// Одно имя print, разные типы параметров: выбор делает компилятор.
void print(int value) {
    std::cout << "print(int): " << value << '\n';
}
void print(double value) {
    std::cout << "print(double): " << value << '\n';
}
void print(const Scores& value) {
    std::cout << "print(Scores): total " << value.total() << '\n';
}
}


namespace {
// Оба преобразования int -> long и int -> double имеют одинаковый ранг.
void choose(long) {
    std::cout << "choose(long)\n";
}
void choose(double) {
    std::cout << "choose(double)\n";
}
}

int main() {

    Scores first{3, 4, 5};
    std::cout << "Total: " << first.total() << '\n';

    print(7);
    print(2.5);
    print(first);

    short small = 6;
    float fraction = 2.5f;
    print(small);     // print(int): promotion
    print(fraction);  // print(double): promotion

    // choose(42);  // Не компилируется: нет лучшей перегрузки.
    // Явный static_cast снимает неоднозначность.
    choose(static_cast<long>(42));
    choose(static_cast<double>(42));

    // operator[] возвращает int&, поэтому элементу можно присвоить значение.
    first[1] = 8;
    const Scores fixed{1, 2, 3};
    std::cout << "Changed element: " << first[1] << '\n';
    std::cout << "Const element: " << fixed[1] << '\n';

    Scores second{1, 2, 3};
    // + возвращает новое значение; += изменит first.
    Scores sum = first + second;
    first += second;
    std::cout << "Sum total: " << sum.total() << '\n';
    std::cout << "Updated total: " << first.total() << '\n';

    // Умножение поддерживается и при int слева, и при Scores слева.
    Scores scaled = 2 * second;
    std::cout << "2 * second: " << scaled.total() << '\n';
    std::cout << "second * 2: " << (second * 2).total() << '\n';

    // operator<< возвращает ostream&, поэтому допускает цепочки <<.
    std::cout << "Scores: " << first << " and " << second << '\n';

    // Составной ключ: сочетание группы и номера.
    StudentId anna{"A", 2};
    StudentId boris{"B", 1};
    std::cout << std::boolalpha;
    std::cout << "anna == boris: " << (anna == boris) << '\n';
    std::cout << "anna < boris: " << (anna < boris) << '\n';
    std::cout << anna << ' ' << boris << '\n';

    // std::map сортирует ключи по operator<
    std::map<StudentId, Scores> results;
    results.emplace(StudentId{"B", 1}, Scores{2, 3, 4});
    results.emplace(StudentId{"A", 2}, Scores{5, 5, 5});
    results.emplace(StudentId{"A", 1}, Scores{1, 3, 5});

    std::cout << "Ordered by group, then number:\n";
    for (const auto& entry : results) {
        std::cout << entry.first << ": " << entry.second << '\n';
    }
    std::cout << "A-2 total: " << results.at(StudentId{"A", 2}).total() << '\n';

    // Третий параметр шаблона задаёт функтор другого порядка.
    std::map<StudentId, Scores, ByNumber> by_number;
    for (const auto& entry : results) {
        by_number.emplace(entry.first, entry.second);
    }
    std::cout << "Ordered by number, then group:\n";
    for (const auto& entry : by_number) {
        std::cout << entry.first << '\n';
    }

    // count_if вызывает функтор-предикат с заданным порогом.
    std::vector<Scores> attempts{{4, 5, 6}, {1, 2, 3}, {9, 8, 1}};
    const auto enough = std::count_if(attempts.begin(), attempts.end(),
                                      AtLeastTotal{15});
    std::cout << "Totals >= 15: " << enough << '\n';
}
