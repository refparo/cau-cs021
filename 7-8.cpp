#include <iostream>

using namespace std;

class Person {
public:
  virtual void name() { cout << "A::name" << endl; }
private:
  virtual void sex() { cout << "A::sex" << endl; }
};

class Student : public Person {
public:
  virtual void name() { cout << "B::name" << endl; }
  virtual void address() { cout << "B::address" << endl; }
private:
  virtual void ID() { cout << "B::ID" << endl; }
};

typedef void (*Fun)(void);

int main() {
  Person person;
  cout << "\nGet Vptr in the Person" << endl;

  for (int i = 0; i < 2; i++) {
    Fun p = *(*((Fun **)(&person)) + i);
    p();
  }
  cout << "\nGet Vptr in the Student" << endl;

  Student stu;
  for (int i = 0; i < 4; i++) {
    Fun p = *(*((Fun **)(&stu)) + i);
    p();
  }
}
