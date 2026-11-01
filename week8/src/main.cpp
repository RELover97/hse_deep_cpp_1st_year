#include "board.hpp"
#include "employee.hpp"
#include "notification.hpp"
#include "report.hpp"
#include "ticket_cache.hpp"
#include "ticket_queue.hpp"
#include "ticket_registry.hpp"
#include <iostream>
#include <memory>

int main() 
{
    TicketQueue line;
    TicketRegistry registry;
    Employee employee;
    Board board;
    TicketCache cache;
    Notifications notifications;

    auto ticket = std::make_shared<Ticket>(101, "Аня");
    registry.add(ticket);           // Реестр действительно владеет талоном.
    line.push(ticket);              // Очередь тоже владеет, пока номер ожидает.
    board.show(ticket);             // Табло лишь наблюдает за живым объектом.
    cache.remember(ticket);         // Поиск не должен продлевать жизнь талона.

    auto phone = std::make_shared<PhoneNotification>("Аня");
    notifications.subscribe(phone); // Подписка не продлевает жизнь приложения.

    auto serving = line.take_next();
    employee.accept(serving);
    registry.print_status(101);     // Обслуживается: реестр видит изменение.
    notifications.announce(*serving);
    phone.reset();                  // Приложение на телефоне закрылось.
    notifications.announce(*serving); // Повторное уведомление не доставляется.

    serving.reset();                // Владелец на уровне main отпущен.
    ticket.reset();
    employee.finish();              // Реестр всё ещё удерживает талон.
    registry.print_status(101);     // Обслужен, ещё доступен посетителю.
    registry.erase(101);            // Теперь и последний владелец отпустил.
    board.print();                  // Слабая ссылка больше не действительна.
    std::cout << "Поиск после обслуживания: "
              << (cache.find(101) ? "найден" : "объект уже удалён") << '\n';

    DailyReport report = build_report();
    std::cout << "Пример отчёта: " << report.served.size() << " номера(ов)\n";
}
