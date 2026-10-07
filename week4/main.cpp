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

class FinancialReport {
public:
    void add(Operation *operation) {
        operations.push_back(std::move(operation));
    }

    double total() const {
        double result = 0.0;

        for (const auto& operation : operations) {
            result += operation->get_amount();
        }

        return result;
    }

    void print() const {
        for (const auto& operation : operations) {
            operation->print();
        }

        std::cout << "----------------\n";
        std::cout << "Total: " << total() << '\n';
    }

private:

    std::vector<Operation*> operations;
};


class IOperationReader {
public:
    virtual ~IOperationReader() = default;

    virtual std::vector<Operation*> read(const std::string &source) const = 0;
};

class SqlReader : public IOperationReader {
public:
    std::vector<Operation*> read(const std::string &source) const override {
        std::cout << "[SQL] Reading from database: "
                  << source << '\n';

        std::cout << "[SQL] Executing query:\n"
                  << "SELECT type, amount, description "
                  << "FROM operations;\n";

        std::vector<Operation*> result;

        result.push_back(new Income(150000, "Salary"));

        result.push_back(new Expense(50000, "Rent"));

        return result;  
    }
};

class ExcelReader : public IOperationReader {
public:
    std::vector<Operation*> read(const std::string &source) const override {
        std::cout << "[SQL] Reading from database: "
                  << source << '\n';

        std::cout << "[SQL] Executing query:\n"
                  << "SELECT type, amount, description "
                  << "FROM operations;\n";

        std::vector<Operation*> result;

        result.push_back(new Income(150000, "Salary"));

        result.push_back(new Expense(50000, "Rent"));

        return result;
    }
};

class DocumentReader : public IOperationReader {
public:
    std::vector<Operation*> read(const std::string &source) const override {
        std::cout << "[Excel] Reading file: "
                  << source << '\n';

        std::vector<Operation*> result;

        result.push_back(new Income(120000, "Freelance"));

        result.push_back(new Expense(15000, "Travel"));

        result.push_back(new Expense(5000, "Food"));

        return result;
    }
};


int main()
{
    std::vector<Operation*> operations {
        new Income(150000, "Salary"),
        new Expense(50000, "Rent"),
        new Transfer(10000, "Debt")
    };

    for (size_t i = 0; i < operations.size(); ++i) {
        operations[i]->print();
    }

    for (const auto &op: operations) {
        delete op;
    }

    return 0;
}