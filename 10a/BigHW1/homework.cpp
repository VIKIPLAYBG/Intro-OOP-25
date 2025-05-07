#include <iostream>
#include <cmath>

using namespace std;

class Operation {

protected:
    string name;
    string symbol;

    void const setName(string name) {
        if(name.empty())
            throw invalid_argument("(Set Name) Name is Empty!");
        this->name = name;
    }

    void const setSymbol(string symbol) {
        if(symbol.empty())
            throw invalid_argument("(Set Symbol) Symbol is Empty!");
        this->symbol = symbol;
    }

public:

    Operation(string name, string symbol) {
        if(name.empty())
            throw invalid_argument("(Original Para Constructor) Name is Empty!");
        if(symbol.empty())
            throw invalid_argument("(Original Para Constructor) Symbol is Empty!");
    }

    Operation(Operation &other) {
        if(other.name.empty())
            throw invalid_argument("(Original Copy Constructor) Name is Empty!");
        if(other.symbol.empty())
            throw invalid_argument("(Original Copy Constructor) Symbol is Empty!");
        this->name = other.name;
        this->symbol = other.symbol;
    }

    Operation &operator=(Operation &other) {
        if(this != &other) {
            if(other.name.empty())
                throw invalid_argument("(Original Operator=) Name is Empty!");
            if(other.symbol.empty())
                throw invalid_argument("(Original Operator=) Symbol is Empty!");
            this->name = other.name;
            this->symbol = other.symbol;
        }
        return *this;
    }

    string getName() const {
        return name;
    }

    string getSymbol() const {
        return name;
    }

    virtual double execute(const double n1, const double n2) const {}

};

class AddOperation : Operation {

public:
    AddOperation() : Operation(name, symbol) {
        if(name.empty())
            throw invalid_argument("(AddOperation Default Constructor) Name is Empty!");
        if(symbol.empty())
            throw invalid_argument("(AddOperation Default Constructor) Symbol is Empty!");
    }

    AddOperation(AddOperation &other) : Operation(other) {
        if(other.name.empty())
            throw invalid_argument("(Original Copy Constructor) Name is Empty!");
        if(other.symbol.empty())
            throw invalid_argument("(Original Copy Constructor) Symbol is Empty!");
        this->name = other.name;
        this->symbol = other.symbol;
    }

    AddOperation &operator=(AddOperation &other) {
        if(this != &other)
            Operation::operator=(other);
        return *this;
    }

    double execute(const double n1, const double n2) const override {
        return n1 + n2;
    }
};

class SubtractOperation : Operation {

public:
    SubtractOperation() : Operation(name, symbol) {
        if(name.empty())
            throw invalid_argument("(AddOperation Default Constructor) Name is Empty!");
        if(symbol.empty())
            throw invalid_argument("(AddOperation Default Constructor) Symbol is Empty!");
    }

    SubtractOperation(SubtractOperation &other) : Operation(other) {
        if(other.name.empty())
            throw invalid_argument("(Original Copy Constructor) Name is Empty!");
        if(other.symbol.empty())
            throw invalid_argument("(Original Copy Constructor) Symbol is Empty!");
        this->name = other.name;
        this->symbol = other.symbol;
    }

    SubtractOperation &operator=(SubtractOperation &other) {
        if(this != &other)
            Operation::operator=(other);
        return *this;
    }

    double execute(const double n1, const double n2) const override {
        return n1 - n2;
    }
};

class MultiplyOperation : Operation {

public:
    MultiplyOperation() : Operation(name, symbol) {
        if(name.empty())
            throw invalid_argument("(AddOperation Default Constructor) Name is Empty!");
        if(symbol.empty())
            throw invalid_argument("(AddOperation Default Constructor) Symbol is Empty!");
    }

    MultiplyOperation(MultiplyOperation &other) : Operation(other) {
        if(other.name.empty())
            throw invalid_argument("(Original Copy Constructor) Name is Empty!");
        if(other.symbol.empty())
            throw invalid_argument("(Original Copy Constructor) Symbol is Empty!");
        this->name = other.name;
        this->symbol = other.symbol;
    }

    MultiplyOperation &operator=(MultiplyOperation &other) {
        if(this != &other)
            Operation::operator=(other);
        return *this;
    }

    double execute(const double n1, const double n2) const override {
        return n1 * n2;
    }
};

class DivideOperation : Operation {

public:
    DivideOperation() : Operation(name, symbol) {
        if(name.empty())
            throw invalid_argument("(AddOperation Default Constructor) Name is Empty!");
        if(symbol.empty())
            throw invalid_argument("(AddOperation Default Constructor) Symbol is Empty!");
    }

    DivideOperation(DivideOperation &other) : Operation(other) {
        if(other.name.empty())
            throw invalid_argument("(Original Copy Constructor) Name is Empty!");
        if(other.symbol.empty())
            throw invalid_argument("(Original Copy Constructor) Symbol is Empty!");
        this->name = other.name;
        this->symbol = other.symbol;
    }

    DivideOperation &operator=(DivideOperation &other) {
        if(this != &other)
            Operation::operator=(other);
        return *this;
    }

    double execute(const double n1, const double n2) const override {
        return n1 / n2;
    }
};

class PowerOperation : Operation {

public:
    PowerOperation() : Operation(name, symbol) {
        if(name.empty())
            throw invalid_argument("(AddOperation Default Constructor) Name is Empty!");
        if(symbol.empty())
            throw invalid_argument("(AddOperation Default Constructor) Symbol is Empty!");
    }

    PowerOperation(PowerOperation &other) : Operation(other) {
        if(other.name.empty())
            throw invalid_argument("(Original Copy Constructor) Name is Empty!");
        if(other.symbol.empty())
            throw invalid_argument("(Original Copy Constructor) Symbol is Empty!");
        this->name = other.name;
        this->symbol = other.symbol;
    }

    PowerOperation &operator=(PowerOperation &other) {
        if(this != &other)
            Operation::operator=(other);
        return *this;
    }

    double execute(const double n1, const double n2) const override {
        return pow(n1, n2);
    }
};

class RootOperation : Operation {

public:
    RootOperation() : Operation(name, symbol) {
        if(name.empty())
            throw invalid_argument("(AddOperation Default Constructor) Name is Empty!");
        if(symbol.empty())
            throw invalid_argument("(AddOperation Default Constructor) Symbol is Empty!");
    }

    RootOperation(RootOperation &other) : Operation(other) {
        if(other.name.empty())
            throw invalid_argument("(Original Copy Constructor) Name is Empty!");
        if(other.symbol.empty())
            throw invalid_argument("(Original Copy Constructor) Symbol is Empty!");
        this->name = other.name;
        this->symbol = other.symbol;
    }

    RootOperation &operator=(RootOperation &other) {
        if(this != &other)
            Operation::operator=(other);
        return *this;
    }

    double execute(const double n1, const double n2) const override {
        if(n1 < 0)
            throw invalid_argument("(Root Operation) Underlying Magnitude is less than 0! (Inaccessible Values)");
        return pow(n1, 1/n2);
    }
};

class Calculator {
    const char* name;
    size_t numberOfSupportedOperations;
    size_t capacityForOperations;
    Operation** operations;
    static double numberOfSuccessfulCalculations;

public:

    Calculator(const char* name, size_t n, Operation** operations) {

    }

    Calculator(const Calculator &other) {

    }

    const Calculator &operator=(const Calculator &other) {

    }

    ~Calculator() {

    }

    void listSupportedOperations() {

    }
};

//Main!!!