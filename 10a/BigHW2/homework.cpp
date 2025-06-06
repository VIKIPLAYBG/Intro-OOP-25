#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

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
        this->salaries = new double[capacity];
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
        this->salaries = new double[other.capacity];
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
            this->salaries = new double[other.capacity];
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
        for(size_t i = 0; i < this->size; i++) {
            tmp[i] = salaries[i];
        }
        delete[] salaries;
        salaries = tmp;
    }

    void addSalary(double newSalary) {
        if(this->size == this->capacity)
            resize();
        salaries[this->size++] = newSalary;
    }
};

class Person {

protected:
    string name; //Mustn't be empty
    int age; //Must be positive and lower than 65
    static int numOfPeople;

public:

    Person(string name, int age) {
        if(name.empty())
            throw invalid_argument("(Person Para Constructor) Name is empty!");
        this->name = name;
        if(age < 0 || age > 65)
            throw invalid_argument("(Person Para Constructor) Age is invalid!");
        this->age = age;
        this->numOfPeople++;
    }

    Person(const Person &other) {
        if(other.name.empty())
            throw invalid_argument("(Person Copy Constructor) Name is empty!");
        this->name = other.name;
        if(other.age < 0 || other.age > 65)
            throw invalid_argument("(Person Copy Constructor) Age is invalid!");
        this->age = other.age;
        this->numOfPeople++;
    }

    Person &operator=(const Person &other) {
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

    virtual int getWorkers() {
        return this->numOfPeople;
    }
};

int Person::numOfPeople = 0;

class Employee : public Person {
    
    EmployeeSalaries* empSalaries;
    string position;
    int experience;
    static int numOfEmployees;

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
        this->numOfEmployees++;
    }

    Employee(const Employee &other) : Person(other) {
        for(size_t i = 0; i < other.empSalaries->getSize(); i++)
            this->empSalaries[i] = other.empSalaries[i];
        if(other.position.empty())
            throw invalid_argument("(Employee Copy Constructor) Position is empty!");
        this->position = other.position;
        if(other.experience < 1)
            throw invalid_argument("(Employee Copy Constructor) Experience is invalid!");
        this->experience = other.experience;
        this->numOfEmployees++;
    }

    Employee &operator=(const Employee &other) {
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

    void addSalary(double salary) {
        empSalaries->addSalary(salary);
    }

    int getWorkers() override {
        return numOfEmployees;
    }
};

int Employee::numOfEmployees = 0;

class Manager : public Person {
    string department; //Can be "delivery", "marketing", "sales", or "human resources"
    static int numOfManagers;

public:
    
    Manager(string department) : Person(name, age) {
        if(department != "delivery" || department != "marketing" || department != "sales" || department != "human resources")
            throw invalid_argument("(Manager Para Constructor) Department is invalid!");
        this->department = department;
        this->numOfManagers++;
    }

    Manager(const Manager &other) : Person(other) {
        if(other.department != "delivery" || other.department != "marketing" || other.department != "sales" || other.department != "human resources")
            throw invalid_argument("(Manager Copy Constructor) Department is invalid!");
        this->department = other.department;
        this->numOfManagers++;
    }

    Manager &operator=(const Manager &other) {
        if(this != &other) {
            Person::operator=(other);
            if(other.department != "delivery" || other.department != "marketing" || other.department != "sales" || other.department != "human resources")
                throw invalid_argument("(Manager Operator=) Department is invalid!");
            this->department = other.department;
        }
        return *this;
    }

    string getDept() {
        return this->department;
    }

    int getWorkers() override {
        return numOfManagers;
    }

    void payEmployeeByName(string empName, vector<Employee> &employees, double salary) {
        for(auto employee : employees) {
            if(empName == employee.getName()) {
                employee.addSalary(salary);
                break;
            }
        }
        throw invalid_argument("(Manager Pay Employee) Employee not found!");
    }
};

int Manager::numOfManagers = 0;

ostream &operator<<(ostream &os, Person &person) {
    os << person.getName() << ' ' << person.getAge();
    return os;
}

istream &operator>>(istream &is, Person &person) {
    string line;
    getline(is, line);

    stringstream ss(line);

    string strName, strAge;
    getline(ss, strName, ',');
    getline(ss, strAge, ',');

    stringstream ssName(strName), ssAge(strAge);

    string name;
    int age;

    ssName >> name;
    ssAge >> age;

    if(name.empty())
        throw invalid_argument("(FileManager Operator>>) Name is empty!");

    if(age < 0 || age > 65)
        throw invalid_argument("(FileManager Operator>>) Age is invalid!");

    person = Person(name, age);
    return is;
}

class FileManager {

    const string in_name, out_name;

public:
    FileManager(string in, string out) : in_name(in), out_name(out) {}

    void read(vector<Person> people, string personName, int personAge) {
        Person person(personName, personAge);
        ifstream inFile(in_name);
        if(!inFile)
            throw runtime_error("(FileManager Read) Cannot open input file!");

        while (!inFile.eof()) {
            inFile >> person;
            people.push_back(person);
        }
        inFile.close();
    }

    void write(const vector<Person> people) {
        ofstream outFile(out_name);
        if(!outFile)
            throw runtime_error("(FileManager Write) Cannot open output file!");

        for(auto p: people) {
            outFile << p << endl;
        }
        outFile.close();
    }
};

int main() {
    try {
        vector<Person> people;
        FileManager manager("read.txt", "write.txt");
        Person person("Antonio Slavkov", 32);
        manager.read(people, "Antonio Slavkov", 32);
        for(auto p : people) {
            cout << p << endl;
        }
        manager.write(people);
    } catch(exception &e) {
        cerr << "Error!" << e.what() << endl;
    }

    return 0;
}