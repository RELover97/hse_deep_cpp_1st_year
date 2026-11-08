#pragma once

#include <string>
#include <vector>

// Таблица «имя гостя -> номер места».
// Одинаковые имена повторно не добавляем.
class SeatsByGuest {
public:

    bool add(const std::string& name, int seat) {
        for (const Record& record : records_) {
            if (record.name == name) {
                return false;
            }
        }
        records_.push_back({name, seat});
        return true;
    }

    // Результат возвращаем через seat, а bool сообщает об успехе поиска.
    bool get(const std::string& name, int& seat) const {
        for (const Record& record : records_) {
            if (record.name == name) {
                seat = record.seat;
                return true;
            }
        }
        return false;
    }

private:
    struct Record {
        std::string name;
        int seat;
    };

    std::vector<Record> records_;
};
