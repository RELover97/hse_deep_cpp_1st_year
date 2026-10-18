#pragma once
#include <ostream>
#include <string>
#include <tuple>

struct StudentId {
    std::string group;
    int number;

    // Равенство составного ключа требует совпадения ОБОИХ полей.
    friend bool operator==(const StudentId& a, const StudentId& b) {
        return a.group == b.group && a.number == b.number;
    }

    // std::tie задаёт лексикографический порядок: группа, затем номер.
    friend bool operator<(const StudentId& a, const StudentId& b) {
        return std::tie(a.group, a.number) < std::tie(b.group, b.number);
    }

    // Определённый внутри friend — скрытая свободная функция (ищется через ADL).
    friend std::ostream& operator<<(std::ostream& out, const StudentId& id) {
        return out << id.group << '-' << id.number;
    }
};