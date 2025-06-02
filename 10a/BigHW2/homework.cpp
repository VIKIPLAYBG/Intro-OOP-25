#include <iostream>
#include <string>

using namespace std;

class EmployeeSalaries {

    double* salaries; //Must be positive, from 910.00 to 2500.00
    size_t size;
    size_t capacity;
    string employeeName;

protected:



public:

    EmployeeSalaries() {
        capacity = 1;
        salaries = new double[capacity];
        employeeName = "";
    }

    EmployeeSalaries(double* salaries, size_t size, size_t capacity, string employeeName) {
        for(size_t i = 0; i < capacity; i++) {
            if(salaries[i] < 910 || salaries[i] > 2500)
                throw invalid_argument("Invalid Salary!");
            this->salaries[i] = salaries[i];
        }
        this->size = size;
        this->capacity = capacity;
        this->employeeName = employeeName;
    }

    EmployeeSalaries(EmployeeSalaries &other) {
        for(size_t i = 0; i < other.capacity; i++) {
            if(other.salaries[i] < 910 || other.salaries[i] > 2500)
                throw invalid_argument("Invalid Salary!");
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
                    throw invalid_argument("Invalid Salary!");
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