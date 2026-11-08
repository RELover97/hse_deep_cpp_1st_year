#include <iostream>
#include <string>

#include "index.hpp"

int main() {
    // Несколько разных специализаций Index: сравним размер кода.
    Index<std::string, int, 16> a;
    Index<int, std::string, 16> b;
    Index<std::string, bool, 16> c;
    Index<int, int, 16> d;
    Index<std::string, std::string, 16> e;

    a.add("Аня", 2);
    b.add(2, "Аня");
    c.add("Аня", true);
    d.add(2, 7);
    e.add("Аня", "подтвердила участие");

    int seat = 0;
    std::string name;
    bool confirmed = false;
    int count = 0;
    std::string status;

    const bool ok = a.get("Аня", seat) && b.get(2, name) &&
                    c.get("Аня", confirmed) && d.get(2, count) &&
                    e.get("Аня", status);
    if (ok) {
        std::cout << seat << ' ' << name << ' ' << confirmed << ' '
                  << count << ' ' << status << '\n';
    }
}
