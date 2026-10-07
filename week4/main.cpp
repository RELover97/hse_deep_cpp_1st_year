#include <string>
#include <iostream>
#include <vector>

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

    virtual void print() const {
        std::cout << "I am an operation" << std::endl;
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

    void print() const {
        std::cout << "Income: " << description << ", " << amount << '\n';
    }
};


class Expense : public Operation {
public:
    Expense(double amount, std::string description)
        : Operation(amount, description) {}

    void print() const {
        std::cout << "Expense: " << description << ", " << amount << '\n';
    }
};

class Transfer : public Operation {
public:
    Transfer(double amount, std::string description)
        : Operation(amount, description) 
    {}

    void print() {
        std::cout << "Transfer: " << description << ", " << amount << '\n';
    }
};


int main()
{
    std::vector<Operation> operations {
        Income(150000, "Salary"),
        Expense(50000, "Rent"),
        Transfer(10000, "Debt")
    };

    for (size_t i = 0; i < operations.size(); ++i) {
        operations[i].print();
    }

    return 0;
}