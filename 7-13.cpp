//StudybarCommentBegin
#include <iostream>

using namespace std;

class Base {
public:
  virtual void f() { cout << "Base::f" << endl; }
  virtual void g() { cout << "Base::g" << endl; }
  virtual void h() { cout << "Base::h" << endl; }
};
//StudybarCommentEnd

class Derive : public Base {
public:
  void f() { cout << "Derive::f" << endl; }
  void h() { cout << "Derive::h" << endl; }
  virtual void g1() { cout << "Derive::g1" << endl; }
};

typedef void (*Fun)(void);

#define peek(obj, j) (*(Fun **)(&obj))[j]

int main() {
  Derive obj;
  for (int i = 0; i < 4; i++)
    peek(obj, i)();
  return 0;
}
