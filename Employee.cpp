#include <iostream>
#include <string>
#include <sstream> // For stringstream
#include <stdexcept> // For invalid_argument
#include <assert.h>

using namespace std;

class Employee {
    private:
        // Fields
        string name;
        string position;
        double salary;
        int experienceYears;
        int id;

        // Static fields 
        static int nextId;
        static int objectCounter;


    private:
        void applyValues(string name, string position, double salary, int experienceYears) {
            setName(name);
            setPosition(position);
            setSalary(salary);
            setExperienceYears(experienceYears);
            id = nextId++;
            objectCounter++;
        }


    public:
        // Constructors
        Employee(string name, string position, double salary, int experienceYears) {
            applyValues(name, position, salary, experienceYears);
        }

        Employee(string name, double salary, int experienceYears) {
            applyValues(name, "Unknown", salary, experienceYears);
        }

        // Destructor
        ~Employee() {
            objectCounter--;
        }


        // Getters
        string getName() {
            return name;
        }

        string getPosition() {
            return position;
        }

        double getSalary() {
            return salary;
        }

        int getExperienceYears() {
            return experienceYears;
        }

        int getId() {
            return id;
        }

        static int getObjectCounter() {
            return objectCounter;
        }


        // Setters
        void setName(string name) {
            this->name = name;
        }

        void setPosition(string position) {
            this->position = position;
        }

        void setSalary(double salary) {
            if (salary <= 0) {
                throw invalid_argument("Salary must be positive");
            }
            this->salary = salary;
        }

        void setExperienceYears(int experienceYears) {
            if (experienceYears < 0) {
            throw invalid_argument("Experience years cannot be negative");
            }
            this->experienceYears = experienceYears;
        }


        // toString
        string toString() {
            stringstream ss;
            ss << "Employee: id - " << id
            << ", name - " << name
            << ", position - " << position
            << ", salary - " << salary
            << ", experienceYears - " << experienceYears;
            return ss.str();
        }
};

int Employee::nextId = 1;
int Employee::objectCounter = 0;


int main() {
    // test5: object counter should be 0
    assert(Employee::getObjectCounter() == 0);
    {

        // test1:
        Employee e1("John", "Janitor", 2000.99, 2);
        assert(e1.getName() == "John");
        assert(e1.getPosition() == "Janitor");
        assert(e1.getSalary() == 2000.99);
        assert(e1.getExperienceYears() == 2);

        string expected = e1.toString();
        assert(!expected.empty());

        // test2:
        e1.setName("Peter");
        e1.setPosition("Manager");
        e1.setSalary(3500.0);
        e1.setExperienceYears(5);

        assert(e1.getName() == "Peter");
        assert(e1.getPosition() == "Manager");
        assert(e1.getSalary() == 3500.0);
        assert(e1.getExperienceYears() == 5);

        // test3:
        bool exceptionThrown = false;
        try {
            e1.setSalary(-100);
        } 
        catch (const invalid_argument&) {
            exceptionThrown = true;
        }
        assert(exceptionThrown == true);

        // test4:
        Employee e2("Marie", "Tester", 1500.0, 1);
        Employee e3("Joe", 2800.0, 4); 
        assert(e2.getId() > e1.getId());
        assert(e3.getId() > e2.getId());


        // test5:
        Employee* e4 = new Employee("Thomas", "Tester", 1400.0, 1);
        assert(Employee::getObjectCounter() == 4);

        delete e4;
        assert(Employee::getObjectCounter() == 3);

        
        Employee* arr = new Employee[3] {
            Employee("Bob", "Analyst", 2100.0, 3),
            Employee("Tom", "Analyst", 2200.0, 3),
            Employee("Bill", "Analyst", 2300.0, 3)
        };
        
        assert(Employee::getObjectCounter() >= 6);
        delete[] arr;
        assert(Employee::getObjectCounter() == 3);
    }

    assert(Employee::getObjectCounter() == 0);
    cout << "All tests passed successfully." << endl;

    return 0;
}