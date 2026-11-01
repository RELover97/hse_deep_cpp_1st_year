#include <iostream>
#include <memory>
#include <string>

struct TrackedTicket {
    int number;
    explicit TrackedTicket(int number) : number(number) {
        std::cout << "Создан талон №" << number << '\n';
    }
    ~TrackedTicket() {
        std::cout << "Удалён талон №" << number << '\n';
    }
};

void count(const std::string& label, const std::shared_ptr<TrackedTicket>& p) {
    std::cout << label << ": сильных владельцев = " << p.use_count() << '\n';
}

int main() {
    auto source = std::make_shared<TrackedTicket>(101);
    count("Талон создан", source); // 1
    auto in_registry = source;
    count("Талон занесён в реестр", source); // 2
    {
        auto employee = source;
        count("Сотрудник тоже владеет", source); // 3
        in_registry.reset();
        count("Реестр удалил запись", source); // 2
    } // Сотрудник завершил работу.
    count("После завершения обслуживания", source); // 1
    source.reset(); // Только теперь уничтожается Ticket.
    std::cout << "Работа завершена\n";
}
