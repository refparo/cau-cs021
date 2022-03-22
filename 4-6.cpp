#include <cmath>
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

class Fraction {
  int n, d;
public:
  Fraction(int numerator = 1, int denominator = 1) {
    n = numerator; d = denominator;
    simplify();
  }

  void simplify() {
    int divisor = gcd(n, d);
    n = n / divisor * (signbit(d) ? -1 : 1);
    d = abs(d) / divisor;
  }

  Fraction operator+(const Fraction &rhs) const& {
    return Fraction(n * rhs.d + rhs.n * d, d * rhs.d);
  }
  Fraction operator-(const Fraction &rhs) const& {
    return Fraction(n * rhs.d - rhs.n * d, d * rhs.d);
  }
  Fraction operator*(const Fraction &rhs) const& {
    return Fraction(n * rhs.n, d * rhs.d);
  }
  Fraction operator/(const Fraction &rhs) const& {
    return Fraction(n * rhs.d * (signbit(rhs.n) ? -1 : 1), d * abs(rhs.n));
  }

  bool operator<(const Fraction &rhs) const& {
    return n * rhs.d < rhs.n * d;
  }
  bool operator<=(const Fraction &rhs) const& {
    return n * rhs.d <= rhs.n * d;
  }
  bool operator>(const Fraction &rhs) const& {
    return n * rhs.d > rhs.n * d;
  }
  bool operator>=(const Fraction &rhs) const& {
    return n * rhs.d >= rhs.n * d;
  }
  bool operator==(const Fraction &rhs) const& {
    return n == rhs.n && d == rhs.d;
  }
  bool operator!=(const Fraction &rhs) const& {
    return n != rhs.n || d != rhs.d;
  }

  friend ostream& operator<<(ostream &out, const Fraction &num) {
    out << num.n;
    if (num.d == 1) return out;
    else return out << '/' << num.d;
  }
  friend istream& operator>>(istream &in, Fraction &num) {
    in >> num.n >> num.d;
    num.simplify();
    return in;
  }
};

//StudybarCommentBegin
int main() {
  Fraction a(1), b(1, 3), c(-3, 9), d(2, -6);

  cin >> a >> b;

  cout << "a= " << a << ", b = " << b << endl;

  cout << a << " + " << b << " = " << a + b << endl;
  cout << a << " - " << b << " = " << a - b << endl;
  cout << a << " * " << b << " = " << a * b << endl;
  cout << a << " / " << b << " = " << a / b << endl;

  cout << "a == b is " << (a == b) << endl;
  cout << "a != b is " << (a != b) << endl;
  cout << "a <= b is " << (a <= b) << endl;
  cout << "a >= b is " << (a >= b) << endl;
  cout << "a < b is " << (a < b) << endl;
  cout << "a > b is " << (a > b) << endl;
  cout << "c == d is " << (c == d) << endl;

  return 1;
}
//StudybarCommentEnd
