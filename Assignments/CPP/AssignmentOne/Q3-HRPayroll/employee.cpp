#include<iostream>
#include<string>
#include<iomanip> 
using namespace std;

class Employee {
private:
    int empId;
    string name;
    string department;
    char grade;
    double basicSalary;
    bool isActive;
    static int employeeCount;

public:
   
    Employee() {
        employeeCount++;
        empId = 1000 + employeeCount;
        isActive = true;
    }

    
    void setName(const string& n) {
        if (!n.empty()) {
            name = n;
        } else {
            cout << "ERROR: Name cannot be empty." << endl;
        }
    }

    void setDepartment(const string& dept) {
        if (dept == "Engineering" || dept == "HR" || dept == "Finance" || dept == "Operations") {
            department = dept;
        } else {
            cout << "ERROR: '" << dept << "' is not a registered department." << endl;
        }
    }

    void setGrade(char g) {
        if (g == 'A' || g == 'B' || g == 'C' || g == 'D') {
            grade = g;
        } else {
            cout << "ERROR: Invalid grade '" << g << "'. Accepted values: A, B, C, D." << endl;
        }
    }

    void setBasicSalary(double salary) {
        if (salary >= 10000.0 && salary <= 500000.0) {
            basicSalary = salary;
        } else {
            cout << "ERROR: Salary must be between Rs.10,000 and Rs.5,00,000. Value rejected." << endl;
        }
    }

    void deactivate() {
        isActive = false;
    }

    int getEmpId() const { return empId; }
    string getName() const { return name; }
    string getDepartment() const { return department; }
    char getGrade() const { return grade; }
    double getBasicSalary() const { return basicSalary; }
    bool getIsActive() const { return isActive; }
    static int getEmployeeCount() { return employeeCount; }

    double computeAllowances() const {
        if (grade == 'A') return basicSalary * 0.40;
        if (grade == 'B') return basicSalary * 0.30;
        if (grade == 'C') return basicSalary * 0.20;
        return basicSalary * 0.10;
    }

    double computeGrossSalary() const {
        return basicSalary + computeAllowances();
    }

    double computeTax() const {
        double grossSalary = computeGrossSalary();
        if (grossSalary <= 50000.0) {
            return 0.0;
        } else if (grossSalary <= 100000.0) { 
            return (grossSalary - 50000.0) * 0.10;
        } else {
            return 5000.0 + ((grossSalary - 100000.0) * 0.20);
        }
    }

    double computeNetSalary() const {
        return computeGrossSalary() - computeTax();
    }

    void printPayslip() const {
        int pct = (grade == 'A') ? 40 : (grade == 'B') ? 30 : (grade == 'C') ? 20 : 10;

        cout << "\n                                        " << endl;
        cout << "       EMPLOYEE PAYSLIP - AUG 2026       " << endl;
        cout << "\n                                         " << endl;
        cout << "Emp ID        : " << empId << endl;
        cout << "Name          : " << name << endl;
        cout << "Department    : " << department << endl;
        cout << "Grade         : " << grade << endl;
        cout << "Status        : " << (isActive ? "Active" : "Inactive") << endl;
        
        
        cout << fixed << setprecision(2);
        cout << "Basic Salary  : Rs. " << basicSalary << endl;
        cout << "Allowances(" << pct << "%): Rs. " << computeAllowances() << endl;
        cout << "Gross Salary  : Rs. " << computeGrossSalary() << endl;
       
        cout << "Tax Deduction : Rs. " << computeTax() << endl;
        cout << "Net Salary    : Rs. " << computeNetSalary() << endl;
        
    }

    void acceptDetails() {
        string n, dept;
        char g;
        double salary;


        while (true) {
            cout << "Enter name: ";
            getline(cin >> ws, n); 
            setName(n);
            if (!name.empty()) break;
        }

        while (true) {
            cout << "Enter department: ";
            cin >> dept;
            setDepartment(dept);
            if (!department.empty() && department == dept) break;
        }

        while (true) {
            cout << "Enter grade: ";
            cin >> g;
            setGrade(g);
            if (grade == g) break;
        }

        while (true) {
            cout << "Enter basic salary: ";
            cin >> salary;
            setBasicSalary(salary);
            if (basicSalary == salary) break;
        }
    }
};

int Employee::employeeCount = 0;

int main() {
   
    Employee e1;
    Employee* e2 = new Employee();
    Employee* e3 = new Employee();

    e1.acceptDetails();
    e2->acceptDetails();
    e3->acceptDetails();

    
    e1.printPayslip();
    e2->printPayslip();
    e3->printPayslip();

    e3->deactivate();
    if (!e3->getIsActive()) {
        cout << "\n" << e3->getName() << " is no longer active. Payroll skipped." << endl;
    }
    
    cout << "Total Employees : " << Employee::getEmployeeCount() << endl;

    delete e2;
    delete e3;
    return 0;
}
