#pragma once

#include <string>
#include <vector>

// Ищем номер места по имени гостя.
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

// Ищем имя гостя по номеру места. Методы почти повторяют код выше.
class GuestsBySeat {
public:
    bool add(int seat, const std::string& name) {
        for (const Record& record : records_) {
            if (record.seat == seat) {
                return false;
            }
        }
        records_.push_back({seat, name});
        return true;
    }

    bool get(int seat, std::string& name) const {
        for (const Record& record : records_) {
            if (record.seat == seat) {
                name = record.name;
                return true;
            }
        }
        return false;
    }

private:
    struct Record {
        int seat;
        std::string name;
    };
    std::vector<Record> records_;
};
