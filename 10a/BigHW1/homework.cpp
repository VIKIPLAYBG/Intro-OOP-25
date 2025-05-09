#include <iostream>
#include <cstring>
#include <vector>
#include <cmath>

using namespace std;

class Operation {
protected:
    string name;
    string symbol;

public:
    Operation(const string& name, const string& symbol) {
        setName(name);
        setSymbol(symbol);
    }

    Operation(const Operation& other) {
        setName(other.name);
        setSymbol(other.symbol);
    }

    Operation& operator=(const Operation& other) {
        if (this != &other) {
            setName(other.name);
            setSymbol(other.symbol);
        }
        return *this;
    }

    string getName() const {
        return name;
    }

    string getSymbol() const {
        return symbol;
    }

    void setName(const string& name) {
        if (name.empty())
            throw invalid_argument("Name is Empty!");
        this->name = name;
    }

    void setSymbol(const string& symbol) {
        if (symbol.empty())
            throw invalid_argument("Symbol is Empty!");
        this->symbol = symbol;
    }

    virtual double execute(const double n1, const double n2) const = 0;

    virtual ~Operation() = default;
};

class AddOperation : public Operation {
public:
    AddOperation() : Operation("add", "+") {}
    AddOperation(const AddOperation& other) : Operation(other) {}
    AddOperation& operator=(const AddOperation& other) {
        Operation::operator=(other);
        return *this;
    }
    double execute(const double n1, const double n2) const override {
        return n1 + n2;
    }
};

class SubtractOperation : public Operation {
public:
    SubtractOperation() : Operation("subtract", "-") {}
    SubtractOperation(const SubtractOperation& other) : Operation(other) {}
    SubtractOperation& operator=(const SubtractOperation& other) {
        Operation::operator=(other);
        return *this;
    }
    double execute(const double n1, const double n2) const override {
        return n1 - n2;
    }
};

class MultiplyOperation : public Operation {
public:
    MultiplyOperation() : Operation("multiply", "*") {}
    MultiplyOperation(const MultiplyOperation& other) : Operation(other) {}
    MultiplyOperation& operator=(const MultiplyOperation& other) {
        Operation::operator=(other);
        return *this;
    }
    double execute(const double n1, const double n2) const override {
        return n1 * n2;
    }
};

class DivideOperation : public Operation {
public:
    DivideOperation() : Operation("divide", "/") {}
    DivideOperation(const DivideOperation& other) : Operation(other) {}
    DivideOperation& operator=(const DivideOperation& other) {
        Operation::operator=(other);
        return *this;
    }
    double execute(const double n1, const double n2) const override {
        if (n2 == 0)
            throw invalid_argument("Cannot divide by zero.");
        return n1 / n2;
    }
};

class PowerOperation : public Operation {
public:
    PowerOperation() : Operation("power", "^") {}
    PowerOperation(const PowerOperation& other) : Operation(other) {}
    PowerOperation& operator=(const PowerOperation& other) {
        Operation::operator=(other);
        return *this;
    }
    double execute(const double n1, const double n2) const override {
        return pow(n1, n2);
    }
};

class RootOperation : public Operation {
public:
    RootOperation() : Operation("root", "v") {}
    RootOperation(const RootOperation& other) : Operation(other) {}
    RootOperation& operator=(const RootOperation& other) {
        Operation::operator=(other);
        return *this;
    }
    double execute(const double n1, const double n2) const override {
        if (n1 < 0 || n2 <= 0)
            throw invalid_argument("Invalid input for root.");
        return pow(n1, 1 / n2);
    }
};

class Calculator {
    string name;
    size_t numberOfSupportedOperations;
    size_t capacityForOperations;
    Operation** operations;
    static double numberOfSuccessfulCalculations;
    vector<string> inputHistory;

public:
    Calculator() {
        this->name = "\0";
        this->capacityForOperations = 2;
        this->numberOfSupportedOperations = 0;
        this->operations = new Operation*[capacityForOperations];
    }

    Calculator(string name, size_t n, Operation** operations) {
        if (name.empty())
            throw invalid_argument("(Calculator Para Constructor) Name is Empty!");
        this->name = name;

        if (n < 1)
            throw invalid_argument("(Calculator Para Constructor) Capacity is Empty!");
        this->capacityForOperations = n;
        this->numberOfSupportedOperations = n;

        this->operations = new Operation*[this->capacityForOperations];

        for (size_t i = 0; i < n; i++) {
            this->operations[i] = operations[i];
        }
    }

    Calculator(const Calculator& other) {
        if (other.name.empty())
            throw invalid_argument("(Calculator Copy Constructor) Name is Empty!");
        this->name = other.name;

        if (other.capacityForOperations < 1)
            throw invalid_argument("(Calculator Copy Constructor) Capacity is Empty!");
        this->capacityForOperations = other.capacityForOperations;

        for (int i = 0; i < capacityForOperations; i++) {
            this->operations[i] = other.operations[i];
        }
    }

    const Calculator& operator=(const Calculator& other) {
        if (this != &other) {
            if (other.name.empty())
                throw invalid_argument("(Calculator Operator=) Name is Empty!");
            this->name = name;

            if (other.capacityForOperations < 1)
                throw invalid_argument("(Calculator Operator=) Capacity is Empty!");
            this->capacityForOperations = other.capacityForOperations;

            this->operations = new Operation*[capacityForOperations];
            for (int i = 0; i < capacityForOperations; i++) {
                this->operations[i] = other.operations[i];
            }
        }
        return *this;
    }

    ~Calculator() {
        for (size_t i = 0; i < numberOfSupportedOperations; i++) {
            delete operations[i];
        }
        delete[] operations;
    }

    void listSupportedOperations() {
        cout << "Supported Operations:\n";
        for (size_t i = 0; i < numberOfSupportedOperations; i++) {
            cout << operations[i]->getSymbol() << " - " << operations[i]->getName() << endl;
        }
    }

    void listInputFormat() {
        cout << "Input Format: ";
        for (auto item : inputHistory) {
            cout << item << " ";
        }
        cout << "= \n";
    }

    Calculator& addOperation(Operation* op) {
        if (numberOfSupportedOperations >= capacityForOperations) {
            capacityForOperations *= 2;
            Operation** newOperations = new Operation*[capacityForOperations];
            for (size_t i = 0; i < numberOfSupportedOperations; i++) {
                newOperations[i] = operations[i];
            }
            delete[] operations;
            operations = newOperations;
        }
        operations[numberOfSupportedOperations++] = op;
        return *this;
    }

    void startCalculation() {
        try {
            double result;
            cin >> result;
            inputHistory.push_back(to_string(result));

            string op;
            while (true) {
                cin >> op;

                if (op == "=") {
                    cout << result << endl;
                    numberOfSuccessfulCalculations++;
                    return;
                }

                double nextNum;
                cin >> nextNum;
                inputHistory.push_back(op);
                inputHistory.push_back(to_string(nextNum));

                Operation* operation = nullptr;
                for (size_t i = 0; i < numberOfSupportedOperations; i++) {
                    if (operations[i]->getSymbol() == op) {
                        operation = operations[i];
                        break;
                    }
                }

                if (operation)
                    result = operation->execute(result, nextNum);
                else
                    throw invalid_argument("Unsupported operation");
            }
        } catch (const exception& e) {
            cout << "Error: " << e.what() << endl;
        }
    }

    double getNumOfSuccessfulCalculations() {
        return numberOfSuccessfulCalculations;
    }
};

double Calculator::numberOfSuccessfulCalculations = 0;

int main() {
    string name;
    cout << "Enter the calculator's name: ";
    cin >> name;

    size_t n;
    cout << "Enter the number of operations: ";
    cin >> n;

    cin.ignore();

    Operation** operations = new Operation*[n];
    cout << "Enter the Operations: " << endl;
    for (size_t i = 0; i < n; i++) {
        string op_name;
        string op_symbol;
        cout << "Enter the name for operation " << i + 1 << ": ";
        cin >> op_name;
        cout << "Enter the symbol for operation " << i + 1 << ": ";
        cin >> op_symbol;
        if(op_symbol == "+")
            operations[i] = new AddOperation();
        if(op_symbol == "-")
            operations[i] = new SubtractOperation();
        if(op_symbol == "*")
            operations[i] = new MultiplyOperation();
        if(op_symbol == "/")
            operations[i] = new DivideOperation();
        if(op_symbol == "^")
            operations[i] = new PowerOperation();
        if(op_symbol == "v")
            operations[i] = new RootOperation();
        operations[i]->setName(op_name);
        operations[i]->setSymbol(op_symbol);
    }

    Calculator calc(name, n, operations);

    int choice;
    do {
        cout << "1. List supported Operations" << endl;
        cout << "2. List input format" << endl;
        cout << "3. Start calculation" << endl;
        cout << "4. Exit" << endl;
        cout << "Choose option: ";

        cin >> choice;

        if (choice == 1) {
            calc.listSupportedOperations();
        } else if (choice == 2) {
            calc.listInputFormat();
        } else if (choice == 3) {
            calc.startCalculation();
        } else if (choice == 4) {
            cout << "Exiting program..." << endl;
            break;
        } else {
            cout << "Invalid option! Please try again." << endl;
        }
    } while (choice != 4);

    return 0;
}
