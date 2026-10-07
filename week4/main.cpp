#include <string>
#include <iostream>

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

    void print() const;

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
    Income salary(150000, "Salary");
    Expense rent(50000, "Rent");
    Transfer to_friend(10000, "Debt");

    salary.print();
    rent.print();
    to_friend.print();

    return 0;
}