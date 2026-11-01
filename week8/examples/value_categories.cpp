#include <iostream>
#include <string>
#include <utility>
#include <vector>

// Пример  показывает, какую реальную работу выполняют перегрузки по ссылкам.
class MessageArchive {
    std::vector<std::string> messages_;

public:
    // Существующая строка должна остаться у вызывающего кода.
    void add(const std::string& message) {
        std::cout << "  add(const string&): сохраняем копию\n";
        messages_.push_back(message);
    }

    // Для временной строки или строки, которую разрешили опустошить,
    // можно передать ресурсы в vector, не копируя все символы.
    void add(std::string&& message) {
        std::cout << "  add(string&&): сохраняем с перемещением\n";
        messages_.push_back(std::move(message));
        // Почему std::move нужен здесь? Имя message -- lvalue-выражение,
        // несмотря на то, что тип параметра -- string&&.
    }

    void print() const {
        for (const auto& message : messages_) {
            std::cout << "    " << message << '\n';
        }
    }
};

// T& нужен, когда функция должна изменить объект вызывающей стороны.
// Для архива не понадобилась третья перегрузка add(string&).
void add_exclamation(std::string& text) {
    text += "!";
}

struct Tracer {
    std::string text;
    explicit Tracer(std::string value) : text(std::move(value)) {}
    Tracer(const Tracer& other) : text(other.text) {
        std::cout << "  Tracer: копирующий конструктор\n";
    }
    Tracer(Tracer&& other) noexcept : text(std::move(other.text)) {
        std::cout << "  Tracer: перемещающий конструктор\n";
    }
};

void take_by_value(Tracer value) {
    std::cout << "  Получено: " << value.text << '\n';
}

int main() {
    std::cout << "1. Одно имя -- разные выражения:\n";
    int n = 10;
    std::cout << "  n = " << n << ", n + 1 = " << n + 1 << '\n';
    // n -- lvalue, n + 1 -- prvalue, std::move(n) -- xvalue.
    int&& same_object = std::move(n); // Лишь ссылка на прежний объект.
    std::cout << "  Адрес n: " << &n << ", через ссылку: " << &same_object << '\n';
    std::cout << "  После std::move(n): same_object = " << same_object << '\n';

    std::cout << "2. Зачем перегрузка add по двум видам ссылок:\n";
    MessageArchive archive;
    std::string draft = "Встреча в пятницу";
    const std::string important = "Не удалять";

    archive.add(draft);                      // lvalue: выбираем const string&.
    archive.add(important);                  // const lvalue: const string&.
    archive.add(std::string{"Новое сообщение"}); // prvalue: string&&.
    archive.add(std::move(draft));           // xvalue: string&&.
    std::cout << "  Сообщения в архиве:\n";
    archive.print();
    // draft остаётся допустимым объектом, но его значение после
    // перемещения не определено заранее. Перезаписываем его.
    draft = "Исправленный черновик";
    add_exclamation(draft);                 // string& меняет именно draft.
    std::cout << "  После add_exclamation(draft): " << draft << '\n';

    std::cout << "3. Категория аргумента и фактическое перемещение -- разное:\n";
    Tracer original{"Текст"};
    take_by_value(original);                // lvalue -> copy.
    take_by_value(std::move(original));     // xvalue -> move.

    std::cout << "4. Именованная rvalue-ссылка является lvalue-выражением:\n";
    std::string&& ref = std::string{"Временная"};
    archive.add(ref);                       // lvalue -> copy.
    archive.add(std::move(ref));            // xvalue -> move.

    std::cout << "5. std::move не удаляет const:\n";
    const Tracer fixed{"Не менять"};
    take_by_value(std::move(fixed));        // const Tracer&& -> copy.
}
