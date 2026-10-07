#include <string>
#include <iostream>
#include <vector>
#include <memory>

class Operation {
public:
    Operation(double a, std::string d)
        : amount(a), description(d) 
    {}

    double get_amount() const {
        return amount;
    }

    std::string get_description() const {
        return description;
    }

    virtual void print() const = 0;

    virtual ~Operation() {
        std::cout << "Destructing Operation" << std::endl;
    }

protected:

    double amount;
    std::string description;
};


class Income : public Operation {
public:

    Income(double amount, std::string description)
        : Operation(amount, description) 
    {}

    void print() const override {
        std::cout << "Income: " << description << ", " << amount << '\n';
    }

    ~Income() {
        std::cout << "Destructing Income" << std::endl;
    }
};


class Expense : public Operation {
public:
    Expense(double amount, std::string description)
        : Operation(amount, description) {}

    void print() const override {
        std::cout << "Expense: " << description << ", " << amount << '\n';
    }

    ~Expense() {
        std::cout << "Destructing Expense" << std::endl;
    }
};

class Transfer : public Operation {
public:
    Transfer(double amount, std::string description)
        : Operation(amount, description) 
    {}

    void print() const override {
        std::cout << "Transfer: " << description << ", " << amount << '\n';
    }

    ~Transfer() {
        std::cout << "Destructing Transfer" << std::endl;
    }
};


int main()
{
    std::vector<std::unique_ptr<Operation>> operations;

    operations.emplace_back(std::make_unique<Income>(150000, "Salary"));
    operations.emplace_back(std::make_unique<Expense>(50000, "Rent"));
    operations.emplace_back(std::make_unique<Transfer>(10000, "Debt"));

    for (size_t i = 0; i < operations.size(); ++i) {
        operations[i]->print();
    }

    return 0;
}