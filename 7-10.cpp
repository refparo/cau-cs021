#include <iostream>

using namespace std;

class Base {
public:
  virtual ~Base() {
    cout << "delete Base class" << endl;
  }
};

class Derived : public Base {
public:
  Derived() {
    p = new int[100];
  }
  ~Derived() {
    cout << "delete new p" << endl;
    delete[] p;
    cout << "delete Derived class" << endl;
  }
private:
  int *p;
};

//StudybarCommentBegin
void fun(Base* b) {
  delete b;
}

int main() {
  Base *B = new Derived();
  fun(B);
  return 0;
}
//StudybarCommentEnd

