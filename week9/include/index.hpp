#pragma once

#include <vector>
#include <cstddef>

// Одна запись «ключ -> значение»; конкретные типы задаёт пользователь
template <typename Key, typename Value>
struct Entry {
    Key key;
    Value value;
};

// Универсальная таблица соответствий с линейным поиском.
template <typename Key, typename Value, std::size_t Capacity>
class Index {
    static_assert(Capacity > 0, "Index capacity must be positive");
public:
    // Новую запись добавляем только при отсутствии такого ключа
    bool add(const Key& key, const Value& value);

    // Возвращаем успех, а найденное значение записываем через ссылку
    bool get(const Key& key, Value& value) const;

    std::size_t size() const;

private:
    std::vector<Entry<Key, Value>> entries_;
};
