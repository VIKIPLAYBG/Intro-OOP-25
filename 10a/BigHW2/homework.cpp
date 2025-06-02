#include <iostream>
#include <string>

using namespace std;

class EmployeeSalaries {

    double* salaries; //Must be positive, from 910.00 to 2500.00
    size_t size;
    size_t capacity;
    string employeeName;

public:

    EmployeeSalaries() {
        capacity = 1;
        salaries = new double[capacity];
        employeeName = "";
    }

    EmployeeSalaries(double* salaries, size_t size, size_t capacity, string employeeName) {
        for(size_t i = 0; i < capacity; i++) {
            if(salaries[i] < 910 || salaries[i] > 2500)
                throw invalid_argument("(Employee Para Constructor) Invalid Salary!");
            this->salaries[i] = salaries[i];
        }
        this->size = size;
        this->capacity = capacity;
        this->employeeName = employeeName;
    }

    EmployeeSalaries(EmployeeSalaries &other) {
        for(size_t i = 0; i < other.capacity; i++) {
            if(other.salaries[i] < 910 || other.salaries[i] > 2500)
                throw invalid_argument("(Employee Copy Constructor) Invalid Salary!");
            this->salaries[i] = other.salaries[i];
        }
        this->size = other.size;
        this->capacity = other.capacity;
        this->employeeName = other.employeeName;
    }

    EmployeeSalaries &operator=(EmployeeSalaries &other) {
        if(this != &other) {
            for(size_t i = 0; i < other.capacity; i++) {
                if(other.salaries[i] < 910 || other.salaries[i] > 2500)
                    throw invalid_argument("(Employee Operator=) Invalid Salary!");
                this->salaries[i] = other.salaries[i];
            }
            this->size = other.size;
            this->capacity = other.capacity;
            this->employeeName = other.employeeName;
        }
        return *this;
    }

    size_t getSize() {
        return this->size;
    }

    size_t getCapacity() {
        return this->capacity;
    }

    string getName() {
        return this->employeeName;
    }

    void resize() {
        this->capacity *= 2;
        double* tmp = new double[this->capacity];
        for(size_t i = 0; i < this->capacity; i++) {
            tmp[i] = salaries[i];
        }
        delete[] salaries;
        salaries = tmp;
    }

    EmployeeSalaries addSalary(double newSalary) {
        if(this->size == this->capacity)
            resize();
        salaries[this->size++] = newSalary;
    }
};

class Person {

protected:
    string name; //Mustn't be empty
    int age; //Must be positive and lower than 65

public:

    Person(string name, int age) {
        if(name.empty())
            throw invalid_argument("(Person Para Constructor) Name is empty!");
        this->name = name;
        if(age < 0 || age > 65)
            throw invalid_argument("(Person Para Constructor) Age is invalid!");
        this->age = age;
    }

    Person(Person &other) {
        if(other.name.empty())
            throw invalid_argument("(Person Copy Constructor) Name is empty!");
        this->name = other.name;
        if(other.age < 0 || other.age > 65)
            throw invalid_argument("(Person Copy Constructor) Age is invalid!");
        this->age = other.age;
    }

    Person &operator=(Person &other) {
        if(this != &other) {
            if(other.name.empty())
                throw invalid_argument("(Person Operator=) Name is empty!");
            this->name = other.name;
            if(other.age < 0 || other.age > 65)
                throw invalid_argument("(Person Operator=) Age is invalid!");
            this->age = other.age;
        }
        return *this;
    }

    string getName() {
        return this->name;
    }

    int getAge() {
        return this->age; 
    }
};

class Employee : public Person {
    EmployeeSalaries* empSalaries;
    string position;
    int experience;

public:
    Employee(EmployeeSalaries* empSalaries, string position, int experience) : Person(name, age) {
        for(size_t i = 0; i < empSalaries->getSize(); i++)
            this->empSalaries[i] = empSalaries[i];
        if(position.empty())
            throw invalid_argument("(Employee Para Constructor) Position is empty!");
        this->position = position;
        if(experience < 1)
            throw invalid_argument("(Employee Para Constructor) Experience is invalid!");
        this->experience = experience;
    }

    Employee(Employee &other) : Person(other) {
        for(size_t i = 0; i < other.empSalaries->getSize(); i++)
            this->empSalaries[i] = other.empSalaries[i];
        if(other.position.empty())
            throw invalid_argument("(Employee Copy Constructor) Position is empty!");
        this->position = other.position;
        if(other.experience < 1)
            throw invalid_argument("(Employee Copy Constructor) Experience is invalid!");
        this->experience = other.experience;
    }

    Employee &operator=(Employee &other) {
        if(this != &other) {
            for(size_t i = 0; i < other.empSalaries->getSize(); i++)
                this->empSalaries[i] = other.empSalaries[i];
            if(other.position.empty())
                throw invalid_argument("(Employee Operator=) Position is empty!");
            this->position = other.position;
            if(other.experience < 1)
                throw invalid_argument("(Employee Operator=) Experience is invalid!");
            this->experience = other.experience;
        }
        return *this;
    }

    string getPos() {
        return position;
    }

    int getExp() {
        return experience;
    }
};

class Manager : public Person {
    string department; //Can be "delivery", "marketing", "sales", or "human resources"

public:
    
};