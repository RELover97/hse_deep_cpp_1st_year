#pragma once
#include <string>
#include <utility>
#include <vector>

struct DailyReport {
    std::string window_name;
    std::vector<int> served;
};

// NRVO: компилятор может создать named непосредственно у вызывающего кода.
inline DailyReport build_report() {
    DailyReport report;
    report.window_name = "Окно 1";
    report.served = {101, 102, 103};
    return report;  // Здесь специально НЕТ std::move(report).
}

// Обязательное устранение копирования (C++17): возвращаем prvalue.
inline DailyReport empty_report() {
    return DailyReport{"Закрытое окно", {}};
}
