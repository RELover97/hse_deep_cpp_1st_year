#include <string>

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

int main()
{

}