#pragma once

#include <cstddef>
#include <vector>

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
    bool add(const Key& key, const Value& value) {
        for (const Entry<Key, Value>& entry : entries_) {
            if (entry.key == key) {
                return false;
            }
        }
        if (entries_.size() >= Capacity) {
            return false;
        }
        entries_.push_back({key, value});
        return true;
    }

    // Возвращаем успех, а найденное значение записываем через ссылку
    bool get(const Key& key, Value& value) const {
        for (const Entry<Key, Value>& entry : entries_) {
            if (entry.key == key) {
                value = entry.value;
                return true;
            }
        }
        return false;
    }

    std::size_t size() const {
        return entries_.size();
    }

private:
    std::vector<Entry<Key, Value>> entries_;
};
