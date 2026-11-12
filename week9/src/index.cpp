#include "index.hpp"

#include <cstddef>
#include <vector>
#include <string>

// Универсальная таблица соответствий с линейным поиском.
template <typename Key, typename Value, std::size_t Capacity>
bool Index<Key, Value, Capacity>::add(const Key& key, const Value& value) {
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

template <typename Key, typename Value, std::size_t Capacity>
bool Index<Key, Value, Capacity>::get(const Key& key, Value& value) const {
    for (const Entry<Key, Value>& entry : entries_) {
        if (entry.key == key) {
            value = entry.value;
            return true;
        }
    }
    return false;
}


template <typename Key, typename Value, std::size_t Capacity>
std::size_t Index<Key, Value, Capacity>::size() const {
    return entries_.size();
}

// explicit instantiations

template class Index<std::string, int, 16>;
template class Index<int, std::string, 16>;
template class Index<std::string, bool, 16>;
template class Index<int, int, 16>;
template class Index<std::string, std::string, 16>;

template class Index<std::string, int, 6>;
template class Index<int, std::string, 6>;
template class Index<std::string, bool, 6>;