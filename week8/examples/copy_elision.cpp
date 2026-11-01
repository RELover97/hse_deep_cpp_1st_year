#include <iostream>

struct Trace {
    Trace() { 
        std::cout << "Ctor\n"; 
    }

    Trace(const Trace&) { 
        std::cout << "Copy ctor\n"; 
    }

    Trace(Trace&&) noexcept { 
        std::cout << "Move ctor\n"; 
    }

    ~Trace() { 
        std::cout << "Dtor\n"; 
    }
};

Trace guaranteed() {
    return Trace{};  // C++17: не требуется создавать промежуточный объект.
}

Trace optional() {
    Trace value;
    return value;  // NRVO разрешено, но не гарантировано.
}

int main() {
    std::cout << "Возврат временного значения:\n";
    Trace a = guaranteed();
    std::cout << "Возврат именованной переменной:\n";
    Trace b = optional();
}
