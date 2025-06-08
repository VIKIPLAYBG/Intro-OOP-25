#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

class EmployeeSalaries {

protected:

    double* empSalaries; //positive, between 910 and 2500
    size_t size;
    size_t capacity;
    string empName;

    void resize()
    {
        this->capacity *= 2;
        double *tmp = new double[this->capacity];
        for (size_t i = 0; i < this->size; i++)
        {
            tmp[i] = this->empSalaries[i];
        }
        delete[] this->empSalaries;
        this->empSalaries = tmp;
    }

public:
    EmployeeSalaries() {
        this->size = 1;
        this->capacity = 2;
        this->empSalaries = new double[size];
        this->empSalaries[0] = 910;
        this->empName = "";
    }

    EmployeeSalaries(double* empSalaries, size_t size, size_t capacity, string empName) {
        this->size = size;
        this->capacity = capacity;
        this->empName = empName;
        this->empSalaries = new double[this->capacity];
        for(size_t i = 0; i < size; i++) {
            if(empSalaries[i] < 910 || empSalaries[i] > 2500)
                throw invalid_argument("(EmployeeSalaries Para Constructor) Salary is invalid!");
            this->empSalaries[i] = empSalaries[i];
        }
    }

    EmployeeSalaries(const EmployeeSalaries &other) {
        this->size = other.size;
        this->capacity = other.capacity;
        this->empName = other.empName;
        this->empSalaries = new double[this->capacity];
        for(size_t i = 0; i < this->size; i++) {
            this->empSalaries[i] = other.empSalaries[i];
        }
    }

    EmployeeSalaries& operator=(const EmployeeSalaries& other) {
        if(this != &other) {
            this->size = other.size;
            this->capacity = other.capacity;
            this->empName = other.empName;
            delete[] this->empSalaries;
            this->empSalaries = new double[this->capacity];
            for(size_t i = 0; i < this->size; i++) {
                this->empSalaries[i] = other.empSalaries[i];
            }
        }
        return *this;
    }

    ~EmployeeSalaries() {
        delete[] this->empSalaries;
    }

    double getAvgSalary() const {
        double sum = 0;
        for(int i = 0; i < this->size; i++) {
            sum += empSalaries[i];
        }
        sum /= this->size;
        return sum;
    }

    void replaceInitialSal(double empSal) {
        if(empSal < 910 || empSal > 2500)
            throw invalid_argument("(EmployeeSalaries Set Salary) Index out of range!");
        this->empSalaries[0] = empSal;
    }

    void addSalary(double salary) {
        if(this->size == this->capacity)
            resize();
        if(salary < 910 || salary > 2500)
            throw invalid_argument("(AddSalary) Salary is invalid!");
        this->empSalaries[size++] = salary;
    }

    size_t getSize() const {
        return this->size;
    }

    size_t getCapacity() const {
        return this->capacity;
    }

    string getName() const {
        return this->empName;
    }

};

class Person {

protected:

    string name; //Cannot be empty
    int age; //Between 0 and 65
    static int count;

public:

    Person(string name, int age) {
        if(name.empty())
            throw invalid_argument("(Person Para Constructor) Name is empty!");
        this->name = name;
        if(age < 0 || age > 65)
            throw invalid_argument("(Person Para Constructor) Age is invalid!");
        this->age = age;
        count++;
    }

    Person(const Person &other) {
        this->name = other.name;
        this->age = other.age;
        count++;
    }

    virtual ~Person() {}

    Person &operator=(const Person &other) {
        if(this != &other) {
            this->name = other.name;
            this->age = other.age;
        }
        return *this;
    }

    string getName() const {
        return name;
    }

    int getAge() const {
        return age;
    }

    static int getCount() {
        return count;
    }

    virtual char getType() const = 0;
};

int Person::count = 0;

class Employee : public Person {

protected:

    string position; //Cannot be empty
    int experience; //1 or greater
    EmployeeSalaries salaries; //All salaries must be valid
    static int eCount;

public:

    Employee(string name, int age, string position, int experience) : Person(name, age) {
        if(position.empty())
            throw invalid_argument("(Employee Para Constructor) Position is empty!");
        this->position = position;
        if(experience < 1)
            throw invalid_argument("(Employee Para Constructor) Experience is invalid!");
        this->experience = experience;
        eCount++;
    }

    Employee(const Employee &other) : Person(other) {
        this->position = other.position;
        this->experience = other.experience;
        eCount++;
    }

    virtual ~Employee() {}

    Employee &operator=(const Employee &other) {
        if(this != &other) {
            Person::operator=(other);
            this->position = other.position;
            this->experience = other.experience;
        }
        return *this;
    }

    string getPos() const {
        return this->position;
    }

    int getExp() const {
        return this->experience;
    }

    int getSalSize() const {
        return this->salaries.getSize();
    }

    double calculateAverageSalary() const {
        return this->salaries.getAvgSalary();
    }

    void addSalary(double salary) {
        this->salaries.addSalary(salary);
    }

    void replaceInitialSalary(double empSal) {
        if(empSal < 910 || empSal > 2500)
            throw invalid_argument("(Employee ReplaceInitialSalary) Salary is invalid!");
        this->salaries.replaceInitialSal(empSal);
    }

    static int getCount() {
        return eCount;
    }

    friend istream &operator>>(istream& is, Employee &emp) {
        string line;
        getline(is, line);

        stringstream ss(line);
        string strName, strAge, strPos, strExp;

        getline(ss, strName);
        getline(ss, strAge);
        getline(ss, strPos);
        getline(ss, strExp);

        stringstream ssName(strName), ssAge(strAge), ssPos(strPos), ssExp(strExp);

        string name, position;
        int age, experience;
        ssName >> name;
        ssAge >> age;
        ssPos >> position;
        ssExp >> experience;

        emp.name = name;
        emp.age = age;
        emp.position = position;
        emp.experience = experience;

        return is;
    }

    friend ostream &operator<<(ostream& os, const Employee &emp) {
        os << "E " << emp.getName() << " " << emp.getAge() << " " << emp.getPos() << " " << emp.getExp() << endl;

        return os;
    }

    char getType() const override {
        return 'E';
    }
};

int Employee::eCount = 0;

class Manager : public Person {

    string department; //"delivery", "marketing", "sales" or "human resources"
    static int mCount;

public:

    Manager(string name, int age, string department) : Person(name, age) {
        if(department != "Delivery" && department != "Marketing" && department != "Sales" && department != "Human Resources")
            throw invalid_argument("(Manager Para Constructor) Department is invalid!");
        this->department = department;
        mCount++;
    }

    Manager(const Manager &other) : Person(other) {
        this->department = other.department;
        mCount++;
    }

    Manager &operator=(const Manager &other) {
        if(this != &other) {
            Person::operator=(other);
            this->department = other.department;
        }
        return *this;
    }

    string getDept() const {
        return this->department;
    }

    static int getCount() {
        return mCount;
    }

    friend istream &operator>>(istream &is, Manager &mng) {
        string line;
        getline(is, line);

        stringstream ss(line);
        string strName, strAge, strDept;

        getline(ss, strName);
        getline(ss, strAge);
        getline(ss, strDept);

        stringstream ssName(strName), ssAge(strAge), ssDept(strDept);

        string name, department;
        int age;
        ssName >> name;
        ssAge >> age;
        ssDept >> department;

        mng.name = name;
        mng.age = age;
        mng.department = department;

        return is;
    }

    friend ostream &operator<<(ostream &os, const Manager &mng) {
        os << "M " << mng.getName() << " " << mng.getAge() << " " << mng.getDept() << endl;

        return os;
    }

    char getType() const override {
        return 'M';
    }
};

int Manager::mCount = 0;

class FileManager {

    const string in_name, out_name;

public:

    FileManager(const string in_name, const string out_name) : in_name(in_name), out_name(out_name) {}

    static void writeInFile(const vector<Person*> &people, string out_name) {
        ofstream out(out_name);
        if(!out.is_open())
            throw runtime_error("(FileManager Write) Output File cannot be opened");

        for (Person* p : people) {
            char type = p->getType();
            if (type == 'E') {
                Employee* e = dynamic_cast<Employee*>(p);
                out << "E " << e->getName() << " " << e->getAge() << " " << e->getPos() << " " << e->getExp() << " " << e->calculateAverageSalary() << endl;
            }
            else if (type == 'M') {
                Manager* m = dynamic_cast<Manager*>(p);
                out << "M " << m->getName() << " " << m->getAge() << " " << m->getDept() << endl;
            }
        }

        out.close();
    }

    static vector<Person*> readFromFile(const string& filename) {
        vector<Person*> result;
        ifstream in(filename);
        if (!in.is_open()) throw runtime_error("Cannot open file for reading!");

        string line;
        while (getline(in, line)) {
            stringstream iss(line);
            char type;
            iss >> type;

            if (type == 'E') {
                string fstName, lastName, pos;
                int age, exp;
                iss >> fstName >> lastName >> age >> pos >> exp;
                string name = fstName + " " + lastName;
                result.push_back(new Employee(name, age, pos, exp));
            }
            else if (type == 'M') {
                vector<string> tokens;
                string token;
                while (iss >> token) tokens.push_back(token);

                if (tokens.size() < 7) continue;

                string mngName = tokens[0] + " " + tokens[1];
                int age = stoi(tokens[2]);

                size_t i = 3;
                string department = "";
                while (i < tokens.size() - 3) {
                    if (!department.empty()) department += " ";
                    department += tokens[i++];
                }

                string empName = tokens[i] + " " + tokens[i + 1];
                double salary = stod(tokens[i + 2]);

                result.push_back(new Manager(mngName, age, department));

                for (auto p : result) {
                    if (p->getType() == 'E') {
                        Employee* e = dynamic_cast<Employee*>(p);
                        if (e && e->getName() == empName) {
                            try {
                                if (e->getSalSize() == 1 && e->calculateAverageSalary() == 910)
                                    e->replaceInitialSalary(salary);
                                else
                                    e->addSalary(salary);
                            } catch (exception& ex) {
                                cerr << "(Read From File) Couldn't add salary: " << ex.what() << endl;
                            }
                        }
                    }
                }
            }
        }

        in.close();
        return result;
    }
};

int main() {

    FileManager fileman("read.txt", "write.txt");
    vector<Person*> people = fileman.readFromFile("read.txt");
    fileman.writeInFile(people, "write.txt");

    for(auto p : people)
        delete p;

    return 0;
}