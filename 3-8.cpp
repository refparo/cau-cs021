#include <cmath>
#include <iomanip>
#include <iostream>

using namespace std;

int gcd(int a, int b) {
  a = abs(a); b = abs(b);
  int tmp;
  while (b != 0) {
    tmp = a;
    a = b;
    b = tmp % b;
  }
  return a;
}

class Rational {
  int n, d;
public:
  Rational(int numerator = 1, int denominator = 1) {
    n = numerator; d = denominator;
    simplify();
  }
  void simplify() {
    int divisor = gcd(n, d);
    n = n / divisor * (signbit(d) ? -1 : 1);
    d = abs(d) / divisor;
  }

  void add(const Rational &lhs, const Rational &rhs) {
    d = lhs.d * rhs.d;
    n = lhs.n * rhs.d + rhs.n * lhs.d;
    simplify();
  }
  void minus(const Rational &lhs, const Rational &rhs) {
    d = lhs.d * rhs.d;
    n = lhs.n * rhs.d - rhs.n * lhs.d;
    simplify();
  }
  void multi(const Rational &lhs, const Rational &rhs) {
    d = lhs.d * rhs.d;
    n = lhs.n * rhs.n;
    simplify();
  }
  void divide(const Rational &lhs, const Rational &rhs) {
    d = lhs.d * abs(rhs.n);
    n = lhs.n * rhs.d * (signbit(rhs.n) ? -1 : 1);
    simplify();
  }

  void printFormal() const { cout << n << '/' << d << '\n'; }
  void printBoth() const {
    cout << "the Formal format of the rational is : ";
    printFormal();
    cout << "the Fixed format of the rational is : "
      << setprecision(2) << fixed << double(n) / d << '\n';
  }
};

//StudybarCommentBegin
int main() {
  int firstN, firstD, secondN, secondD;
  char op;

  cin >> firstN;
  cin >> firstD;
  cin >> secondN;
  cin >> secondD;

  Rational r1(firstN, firstD), r2(secondN, secondD), r3;

  cin >> op;

  cout << "the Formal format of the first rational is : ";
  r1.printFormal();
  cout << "the Formal format of the second rational is : ";
  r2.printFormal();
  cout << endl;

  switch (op) {
  case '+':
    r3.add(r1, r2);
    r3.printBoth();
    break;
  case '-':
    r3.minus(r1, r2);
    r3.printBoth();
    break;
  case '*':
    r3.multi(r1, r2);
    r3.printBoth();
    break;
  case '/':
    r3.divide(r1, r2);
    r3.printBoth();
    break;
  default:
    cout << "Invalid operator!";
  }

  return 0;
}
//StudybarCommentEnd
