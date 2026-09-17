
#include <iostream>
#include <string>
using namespace std;

class Employee
{
private:
    int empId;
    string name;
    double salary;
    int performanceRating;

public:
    Employee(int id, string eName, double eSal, int eRating)
    {
        empId = id;
        name = eName;
        salary = eSal;
        performanceRating = eRating;
    }
    double calculateBonus()
    {
        if (performanceRating == 5)
            return salary * 0.20;
        if (performanceRating == 4)
            return salary * 0.15;
        if (performanceRating == 3)
            return salary * 0.10;
        if (performanceRating == 2)
            return salary * 0.05;
        return 0.0;
    }
    void displayDetails() const
    {
        string idStr = "";
        if (empId < 10)
        {
            idStr = "00" + to_string(empId);
        }
        else if (empId < 100)
        {
            idStr = "0" + to_string(empId);
        }
        else
        {
            idStr = to_string(empId);
        }

        cout << "ID" << idStr << "| Name : " << name << " | Salary :" << salary << " | Rating : " << performanceRating << " | Bonus : " << calculateBonus() << endl;
    };
    string getName() const
    {
        return name;
    }
};

int main()
{
    Employee *employees[5];

    employees[0] = new Employee(1, "Raj Kumar", 50000, 4);
    employees[1] = new Employee(2, "Priya Singh", 50000, 5);
    employees[2] = new Employee(3, "Arun Patel", 50000, 3);
    employees[3] = new Employee(4, "Deepa Sharma", 50000, 4);
    employees[4] = new Employee(5, "Vikram Singh", 50000, 2);

    for (int i = 0; i < 5; i++)
    {
        employees[i]->displayDetails();
    }

    int maxIndex = 0;
    for (int i = 1; i < 5; i++)
    {
        if (employees[i]->calculateBonus() > employees[maxIndex]->getName())
        {
            maxIndex = i;
        }
    };

    cout << "Employee with maximum bonus :" << employees[maxIndex]->getName();

    for (int i = 0; i < 5; i++)
    {
        delete employees[i];
    }

    return 0;
}
