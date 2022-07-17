# Employee management v2

The second version of employee management uses binary files to store employees and departments, each department must have at least one manager and also can change registered employees/department fields . It has the following features:

![Alt text](https://github.com/ja1za1/Employee-management-v2/blob/main/imgs/photo(introduction).png)

## 1. Department registration
   Register a department with a serial(automatically asigned by the program, starting by 1) ID, a name, the manager ID, the initials and its branch. The ID and name      fields can't be empty, branch field must have only numbers, manager ID must be a registered employee (or 0 if there are no employees registered) on the employee        file (employee.dat). 
   
   ![Alt text](https://github.com/ja1za1/Employee-management-v2/blob/main/imgs/photo(dptregistration).png)

## 2. Employee registration
   Register an employee with an serial(automatically asigned by the program, starting by 1) ID, an unique registry, a name, a birthday, CPF, its department ID, salary,    address(street, district, number, complement, city, uf, cep), email. The registry and name field can't be empty, must validate birthday date and CPF, department ID    must be a registered department on the department file (department.dat).
   
   ![Alt text](https://github.com/ja1za1/Employee-management-v2/blob/main/imgs/photo(employeeregistration).png)

## 3. Change employee
   Change data of an employee with the same registry given by the user. Must follow the same rules of employee registration. If the user changes the employee              department, must create an register on the EmployeeHistory.dat file.
   
   ![Alt text](https://github.com/ja1za1/Employee-management-v2/blob/main/imgs/photo(changeemployee).png)

## 4. Change employee department
   Change the department of an employee with the same registry given by the user. Must create an register on the EmployeeHistory.dat file.
   
   ![Alt text](https://github.com/ja1za1/Employee-management-v2/blob/main/imgs/photo(changeemployeedept).png)

## 5. Change department manager
   Change the manager of a department with the same ID given by the user. Must create an register on the DepartmentHistory.dat file.
   
   ![Alt text](https://github.com/ja1za1/Employee-management-v2/blob/main/imgs/photo(changedeptmanager).png)
   
## 6. Employee query by registry
   Shows all data and department name related to a employee with the same registry given by the user.
   
   ![Alt text](https://github.com/ja1za1/Employee-management-v2/blob/main/imgs/photo(queryemployeeregistry).png)

## 7. Generate payroll
   Shows a report with the employee registry, name and salary.
   
   ![Alt text](https://github.com/ja1za1/Employee-management-v2/blob/main/imgs/photo(generatepayroll).png)

## 8. Change employee salary
   Updates the salary of an employee with the same registry given by the user and updates the SalaryHistory.dat file.
   
   ![Alt text](https://github.com/ja1za1/Employee-management-v2/blob/main/imgs/photo(changeemployeesalary).png)

## 9. Employees by department
   Shows a report of all departments and its employees.
   
   ![Alt text](https://github.com/ja1za1/Employee-management-v2/blob/main/imgs/photo(employeesbydept).png)

## 10. Salary history in a period
   Shows the salary history of an employee with the same registry given by the user.
   
   ![Alt text](https://github.com/ja1za1/Employee-management-v2/blob/main/imgs/photo(salaryhistory).png)

## 11. Department manager
   Shows all data related to the manager of a department with the same ID given by the user.
   
   ![Alt text](https://github.com/ja1za1/Employee-management-v2/blob/main/imgs/photo(deptmanagers).png)

## 12. List departments
   Shows all departments registered on file department.dat
   
   ![Alt text](https://github.com/ja1za1/Employee-management-v2/blob/main/imgs/photo(listdept).png)

## 13. List employees
   Shows all employees registered on file employees.dat
   
   ![Alt text](https://github.com/ja1za1/Employee-management-v2/blob/main/imgs/photo(listemployees).png)
