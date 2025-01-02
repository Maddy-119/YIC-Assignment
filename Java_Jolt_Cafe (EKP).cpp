#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

int social_security_tax = 10;

class Employee 
{
private:
    int employeeid;
    string employeename;
    string employeeposition;
    string employeetype;
    string startdate;
    double basicsalary;

public:
    int getEmployeeID() { return employeeid; }
    string getName() { return employeename; }
    string getPosition() { return employeeposition; }
    string getEmployeeType() { return employeetype; }
    string getStartDate() { return startdate; }
    double getBasicSalary() { return basicsalary; }

    virtual ~Employee() {} // Virtual destructor to make the class polymorphic

    Employee() : employeeid(0), employeename(""), employeeposition(""), employeetype(""), startdate(""), basicsalary(0.0) {}

    void inputempdata() 
    {
        cout << "Enter Employee ID: ";
        cin >> employeeid;
        cout << "Enter Employee Name: ";
        cin.ignore();
        getline(cin, employeename);

        while (true) 
        {
            cout << "Enter Employee Position (Barista, Cashier, Supervisor, Cleaner, Kitchen Staff, Waiter, Waitress): ";
            getline(cin, employeeposition);

            transform(employeeposition.begin(), employeeposition.end(), employeeposition.begin(), ::tolower);

            if (employeeposition == "barista") 
            {
                basicsalary = 1920;
                employeetype = "fulltime";
                break;
            } 
            else if (employeeposition == "cashier") 
            {
                basicsalary = 1790;
                employeetype = "fulltime";
                break;
            } 
            else if (employeeposition == "cleaner") 
            {
                basicsalary = 1400;
                employeetype = "parttime";
                break;
            } 
            else if (employeeposition == "kitchen staff") 
            {
                basicsalary = 1850;
                employeetype = "parttime";
                break;
            } 
            else if (employeeposition == "waiter" || employeeposition == "waitress") 
            {
                basicsalary = 1700;
                employeetype = "parttime";
                break;
            } 
            else if (employeeposition == "supervisor") 
            {
                basicsalary = 2400;
                employeetype = "fulltime";
                break;
            } 
            else 
            {
                cout << "!!! Invalid Employee Position. Please try again !!!" << endl;
            }
        }

        cout << "Enter Employee start date: ";
        getline(cin, startdate);
    }

    void displayempdata() {
        cout << left << setw(15) << "Employee ID" << setw(15) << "Name" << setw(15) << "Position" << setw(15)
             << "Type" << setw(15) << "Start Date" << setw(15) << "Basic Salary" << endl;
        cout << left << setw(15) << employeeid << setw(15) << employeename << setw(15) << employeeposition
             << setw(15) << employeetype << setw(15) << startdate << setw(15) << fixed << setprecision(2) << basicsalary;
    }
};

class Fulltime : public Employee {
private:
    int leaveday;
    float overtimehrs;
    double overtimefee;
    double totalamount;
    double netsalary;
    double bonus = 0;

public:
    Fulltime() : leaveday(0), overtimehrs(0.0), totalamount(0.0), netsalary(0.0) {}

    void inputfulltimedata() 
    {
        inputempdata();
        cout << "Enter leave day number: ";
        cin >> leaveday;
        cout << "Enter overtime hours: ";
        cin >> overtimehrs;
        if (leaveday == 0) 
        {
            bonus = 300;
        } 
        else if (leaveday == 1) 
        {
            bonus = 200;
        } 
        else if (leaveday == 2) 
        {
            bonus = 100;
        } 
        else 
        {
            bonus = 0;
        }
        calculateFulltimetotalsalary();
    }

    double calculateFulltimetotalsalary() 
    {
        double salary = getBasicSalary();
        double bonus = (leaveday == 0) ? 300 : ((leaveday == 1) ? 200 : ((leaveday ==2 ) ? 100 : 0));
        overtimefee = ((salary / 30) / 8) * overtimehrs * 2;

        totalamount = salary + bonus + overtimefee;
        netsalary = totalamount - ((totalamount / 100) * 2) - social_security_tax;
        return netsalary;
    }

    void getFullTimeData()
    {
        displayempdata();
        cout << "Net Salary: $" << fixed << setprecision(2) << netsalary << endl;
    }

    double getNetSalary() { return netsalary; }
    int getLeaveDay() { return leaveday; }
    double getOvertimeHours() { return overtimehrs; }
    double getBonus() { return bonus; }
};

class PartTime : public Employee 
{
private:
    double workinghrs;
    double hourlywage;
    double totalamount;
    double netsalary;

public:
    PartTime() : workinghrs(0), hourlywage(0), totalamount(0), netsalary(0) {}

    void inputparttimedata() 
    {
        inputempdata();
        cout << "Enter working hours (monthly): ";
        cin >> workinghrs;
        
        calculateParttimeTotalNetSalary();
    }

    double calculateParttimeTotalNetSalary() 
    {
        hourlywage = (getBasicSalary() / 30) / 8;
        totalamount = hourlywage * workinghrs;
        netsalary = totalamount;
        return netsalary;
    }

    void getParttimeData()
    {
        displayempdata();
        cout << "Net Salary: $" << fixed << setprecision(2) << netsalary <<endl;
    }

    double getNetSalary() { return netsalary; }
    double getWorkingHours() { return workinghrs; }
    double getHourlyWage() { return hourlywage; }
    double getPartNetSalary() { return netsalary; }
};

struct EmployeeInfo {
    string type;
    double net_salary;
    int employee_id;
    string employee_name;
};

// Merge sort implementation
void merge(vector<EmployeeInfo>& employees, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    vector<EmployeeInfo> leftArr(n1);
    vector<EmployeeInfo> rightArr(n2);

    for (int i = 0; i < n1; i++) leftArr[i] = employees[left + i];
    for (int i = 0; i < n2; i++) rightArr[i] = employees[mid + 1 + i];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (leftArr[i].net_salary >= rightArr[j].net_salary) {
            employees[k] = leftArr[i];
            i++;
        } else {
            employees[k] = rightArr[j];
            j++;
        }
        k++;
    }

    while (i < n1) employees[k++] = leftArr[i++];
    while (j < n2) employees[k++] = rightArr[j++];
}

void mergeSort(vector<EmployeeInfo>& employees, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(employees, left, mid);
        mergeSort(employees, mid + 1, right);
        merge(employees, left, mid, right);
    }
}

vector<Fulltime> Fulltime_Employees;
vector<PartTime> PartTime_Employees;

int main() 
{
    int choose = 0;
    int fulltime_employee = 0, parttime_employee = 0;
    double fulltime_employee_salary = 0, parttime_employee_salary = 0, Total_monthly = 0;

    cout <<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" <<endl;
    cout <<"-------!!!! Java Jolt Cafe !!!!-------" <<endl;
    cout <<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" <<endl;

    while (choose != 5) 
    {
        cout << "\n########## Menu ##########" <<endl;
        cout << "1. Insert Employee Data" <<endl;
        cout << "2. View Full-Time Employees" <<endl;
        cout << "3. View Part-Time Employees" <<endl;
        cout << "4. View all employee " <<endl;
        cout << "5. Exit" <<endl;

        cout << "Choose an option: ";
        cin >> choose;
        cout<<endl;

        switch (choose) 
        {
        case 1: 
        {
            string type;
            cout << "Enter employee type (fulltime/parttime): ";
            cin >> type;
            if (type == "fulltime") 
            {
                Fulltime emp;
                emp.inputfulltimedata();
                Fulltime_Employees.push_back(emp);
                fulltime_employee++;
                fulltime_employee_salary += emp.calculateFulltimetotalsalary();
            } 
            else if (type == "parttime") 
            {
                PartTime emp;
                emp.inputparttimedata();
                PartTime_Employees.push_back(emp);
                parttime_employee++;
                parttime_employee_salary += emp.calculateParttimeTotalNetSalary();
            } 
            else 
            {
                cout << "!!! Invalid type !!!" << endl;
            }

            Total_monthly = fulltime_employee_salary + parttime_employee_salary;
            cout << "!!!! Employee data added successfully !!!!" <<endl;
            break;
        }
        case 2:
            if (Fulltime_Employees.empty())
            {
                cout << "No Full-Time Employees Found!" <<endl;
            }
            else
            {
                for (int i = 0; i < Fulltime_Employees.size(); i++)
                {
                    cout << "\nFull-Time Employee " << i + 1 << ":" <<endl;
                    Fulltime_Employees[i].getFullTimeData();
                }
            }
            break;
        case 3:
            if (PartTime_Employees.empty())
            {
                cout << "No Part-Time Employees Found!" <<endl;
            }
            else
            {
                for (int i = 0; i < PartTime_Employees.size(); i++)
                {
                    cout << "\nPart-Time Employee " << i + 1 << ":" <<endl;
                    PartTime_Employees[i].getParttimeData();
                }
            }
            break;
        case 4: 
        {
            struct EmployeeInfo
            {
                string type;                 // "FullTime" or "PartTime"
                double net_salary;           // Net salary for sorting
                int employee_id;             // Employee ID
                string employee_name;        // Employee Name
                Employee *employee_instance; // Pointer to original object
            };

            vector<EmployeeInfo> all_employees;

            // Collect full-time employees
            for (int i = 0; i < Fulltime_Employees.size(); i++)
            {
                EmployeeInfo info;
                info.type = "FullTime";
                info.net_salary = Fulltime_Employees[i].calculateFulltimetotalsalary();
                info.employee_id = Fulltime_Employees[i].getEmployeeID();
                info.employee_name = Fulltime_Employees[i].getName();
                info.employee_instance = &Fulltime_Employees[i];
                all_employees.push_back(info);
            }

            // Collect part-time employees
            for (int i = 0; i < PartTime_Employees.size(); i++)
            {
                EmployeeInfo info;
                info.type = "PartTime";
                info.net_salary = PartTime_Employees[i].calculateParttimeTotalNetSalary();
                info.employee_id = PartTime_Employees[i].getEmployeeID();
                info.employee_name = PartTime_Employees[i].getName();
                info.employee_instance = &PartTime_Employees[i];
                all_employees.push_back(info);
            }

            for (auto& emp : Fulltime_Employees) 
            {
                all_employees.push_back({"FullTime", emp.getNetSalary(), emp.getEmployeeID(), emp.getName()});
            }
            for (auto& emp : PartTime_Employees) 
            {
                all_employees.push_back({"PartTime", emp.getNetSalary(), emp.getEmployeeID(), emp.getName()});
            }

            if (all_employees.empty())
            {
                cout << "No employees found to display!" <<endl;
                break;
            }

            cout << "\n-----### Sorted by Employees Total Net Salary (High to Low) ###-----\n";
            cout << left << setw(5) << "No"
                 << setw(10) << "ID"
                 << setw(12) << "Name"
                 << setw(12) << "Position"
                 << setw(12) << "Type"
                 << setw(12) << "Net Salary"
                 << setw(12) << "Details" <<endl;

            // Table Rows
            for (int i = 0; i < all_employees.size(); i++)
            {
                cout << left << setw(5) << i + 1
                     << setw(10) << all_employees[i].employee_id
                     << setw(12) << all_employees[i].employee_name;

                // Determine type and display additional details
                if (all_employees[i].type == "FullTime")
                {
                    Fulltime *emp = dynamic_cast<Fulltime *>(all_employees[i].employee_instance);
                    if (emp)
                    {
                        cout << setw(12) << emp->getPosition()
                             << setw(12) << "FullTime"
                             << setw(12) << fixed << setprecision(2) << emp->getNetSalary()
                             << " Leave: " << emp->getLeaveDay()
                             << ", Overtime: " << emp->getOvertimeHours()
                             << ", Bonus: " << emp->getBonus();
                    }
                    else
                    {
                        cout << " [Error: Invalid FullTime cast]";
                    }
                }
                else if (all_employees[i].type == "PartTime")
                {
                    PartTime *emp = dynamic_cast<PartTime *>(all_employees[i].employee_instance);
                    if (emp)
                    {
                        cout << setw(12) << emp->getPosition()
                             << setw(12) << "PartTime"
                             << setw(12) << fixed << setprecision(2) << emp->getNetSalary()
                             << " Hours: " << emp->getWorkingHours()
                             << ", Wage: " << emp->getHourlyWage();
                    }
                    else
                    {
                        cout << " [Error: Invalid PartTime cast]";
                    }
                }
                cout << endl<<endl;
            }

            cout << "***************************************************************" <<endl;
            cout << "Monthly Fulltime Salary Cost" <<endl;
            cout << "-------------------------------------" <<endl;
            cout << "Total Fulltime Employee: " << fulltime_employee <<endl;
            cout << "Total Fulltime Salary Cost (Monthly): " << fulltime_employee_salary <<endl<<endl;

            cout << "Monthly Parttime Salary Cost " << endl;
            cout << "-------------------------------------" <<endl;
            cout << "Total Parttime Employee : " << parttime_employee <<endl;
            cout << "Total Parrttime Salary Cost (Monthly): " << parttime_employee_salary <<endl<<endl;
            
            cout << "Total Monthly Salary of All Employee : " << Total_monthly <<endl;
            cout << "***************************************************************" <<endl;
            break;
        }
        case 5:
            cout << "Exiting program...\n";
            break;
        default:
            cout << "Invalid option! Try again.\n";
        }
    }
    return 0;
}