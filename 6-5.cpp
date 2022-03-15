#include <iostream>
#include <istream>
#include <ostream>

using namespace std;

template<typename T>
T isEqualTo(T lhs, T rhs) {
  return lhs == rhs;
}

class SomeClass {
  int a; double b;
public:
  SomeClass(int a = 1, double b = 1.1): a(a), b(b) {}
  friend bool isEqualTo(const SomeClass &lhs, const SomeClass &rhs) {
    return lhs.a == rhs.a && lhs.b == rhs.b;
  }
  friend ostream& operator<<(ostream &out, const SomeClass &obj) {
    return out << '(' << obj.a << ',' << obj.b << ')';
  }
  friend istream& operator>>(istream &in, SomeClass &obj) {
    return in >> obj.a >> obj.b;
  }
};

//StudybarCommentBegin
int main() {
  int a;
  int b;

  cin >> a >> b;

  char c;
  char d;

  cin >> c >> d;

  double e;
  double f;

  cin >> e >> f;

  SomeClass g(1, 1.1);
  SomeClass h;

  cin >> h;

  cout << a << " and " << b << " are "
       << (isEqualTo(a, b) ? "equal" : "not equal") << '\n';

  cout << c << " and " << d << " are "
       << (isEqualTo(c, d) ? "equal" : "not equal") << '\n';

  cout << e << " and " << f << " are "
       << (isEqualTo(e, f) ? "equal" : "not equal") << '\n';

  cout << "The class objects " << g << " and " << h << " are "
       << (isEqualTo(g, h) ? "equal" : "not equal") << '\n';

  return 0;
}
//StudybarCommentEnd
