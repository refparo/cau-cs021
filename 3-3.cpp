#include <iostream>

using namespace std;

class Employee {
  string forename, surname;
  int wage;
public:
  Employee(string firstName, string lastName, int monthlySalary) {
    forename = firstName;
    surname = lastName;
    wage = max(monthlySalary, 0);
  }
  string getFirstName() const { return forename; }
  void setFirstName(string firstName) { forename = firstName; }
  string getLastName() const { return surname; }
  void setLastName(string lastName) { surname = lastName; }
  int getMonthlySalary() const { return wage; }
  void setMonthlySalary(int monthlySalary) { wage = max(monthlySalary, 0); }
};

//StudybarCommentBegin
int main() {
  Employee employee1("Lisa", "Roberts", 4500);
  Employee employee2("Mark", "Stein", 4000);

  cout << "Employees' yearly salaries: " << endl;

  int monthlySalary1 = employee1.getMonthlySalary();
  cout << employee1.getFirstName() << " " << employee1.getLastName()
    << ": $" << monthlySalary1 * 12 << endl;

  int monthlySalary2 = employee2.getMonthlySalary();
  cout << employee2.getFirstName() << " " << employee2.getLastName()
    << ": $" << monthlySalary2 * 12 << endl;

  employee1.setMonthlySalary(int(monthlySalary1 * 1.1));
  employee2.setMonthlySalary(int(monthlySalary2 * 1.1));

  cout << "\nEmployees' yearly salaries after 10% raise: " << endl;

  monthlySalary1 = employee1.getMonthlySalary();
  cout << employee1.getFirstName() << " " << employee1.getLastName()
    << ": $" << monthlySalary1 * 12 << endl;

  monthlySalary2 = employee2.getMonthlySalary();
  cout << employee2.getFirstName() << " " << employee2.getLastName()
    << ": $" << monthlySalary2 * 12 << endl;
  return 0;
}
//StudybarCommentEnd
