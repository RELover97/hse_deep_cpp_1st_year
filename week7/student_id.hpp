#pragma once
#include <ostream>
#include <string>
#include <tuple>
#include <functional>
#include <stddef.h> // size_t в глобальном пространстве имён
#include <compare>

struct StudentId {
    std::string group;
    int number;

    // C++20: поля сравниваются по порядку объявления — сначала group, потом number.
    // Из defaulted <=> также неявно создаётся operator==; остальные операции
    // (<, >, <=, >=, !=) могут использовать эти сравнения через правила переписывания.
    auto operator<=>(const StudentId& other) const = default;

    // Определённый внутри friend — скрытая свободная функция (ищется через ADL).
    friend std::ostream& operator<<(std::ostream& out, const StudentId& id) {
        return out << id.group << '-' << id.number;
    }

    // Hidden friend: обычный поиск имени не находит эту функцию.
    // Неквалифицированный вызов sameGroup(a, b) работает благодаря ADL.
    friend bool sameGroup(const StudentId& a, const StudentId& b) {
        return a.group == b.group;
    }
};

// Функтор задаёт иной порядок для map, не меняя operator< StudentId.
struct ByNumber {
    bool operator()(const StudentId& a, const StudentId& b) const {
        // Учитываем оба поля: ключи с одним номером, но разными группами не равны.
        return std::tie(a.number, a.group) < std::tie(b.number, b.group);
    }
};

// Хэшер для unordered_map: равные ключи обязаны иметь одинаковый хэш.
struct StudentHash {
    size_t operator()(const StudentId& id) const noexcept {
        size_t h1 = std::hash<std::string>{}(id.group);
        size_t h2 = std::hash<int>{}(id.number);
        // Смешиваем хэши обоих полей; коллизии всё равно возможны.
        return h1 ^ (h2 + 0x9e3779b9u + (h1 << 6) + (h1 >> 2));
    }
};