//StudybarCommentBegin
#include <iostream>

using namespace std;

class Fraction {
  int numerator, denominator;

public:
  Fraction(int a, int b);

  bool operator==(Fraction const &f) const;
  bool operator!=(Fraction const &f) const;
  bool operator>(Fraction const &f) const;
  bool operator>=(Fraction const &f) const;
  bool operator<(Fraction const &f) const;
  bool operator<=(Fraction const &f) const;

  Fraction operator+(Fraction const &f) const;
  Fraction operator-(Fraction const &f) const;
  Fraction operator*(Fraction const &f) const;
  Fraction operator/(Fraction const &f) const;

  friend std::istream& operator>>(std::istream &, Fraction &f);
  friend std::ostream& operator<<(std::ostream &, Fraction const &f);

private:
  void simplify(); //私有的化简分数用的函数。
};
//StudybarCommentEnd

#include <cmath>

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

Fraction::Fraction(int a, int b = 1) : numerator(a), denominator(b) {
  simplify();
}

void Fraction::simplify() {
  int divisor = gcd(numerator, denominator);
  numerator = numerator / divisor * (signbit(denominator) ? -1 : 1);
  denominator = abs(denominator) / divisor;
}

Fraction Fraction::operator+(const Fraction &rhs) const {
  return Fraction(numerator * rhs.denominator + rhs.numerator * denominator,
    denominator * rhs.denominator);
}
Fraction Fraction::operator-(const Fraction &rhs) const {
  return Fraction(numerator * rhs.denominator - rhs.numerator * denominator,
    denominator * rhs.denominator);
}
Fraction Fraction::operator*(const Fraction &rhs) const {
  return Fraction(numerator * rhs.numerator, denominator * rhs.denominator);
}
Fraction Fraction::operator/(const Fraction &rhs) const {
  return Fraction(
    numerator * rhs.denominator * (signbit(rhs.numerator) ? -1 : 1),
    denominator * abs(rhs.numerator));
}

bool Fraction::operator<(const Fraction &rhs) const {
  return numerator * rhs.denominator < rhs.numerator * denominator;
}
bool Fraction::operator<=(const Fraction &rhs) const {
  return numerator * rhs.denominator <= rhs.numerator * denominator;
}
bool Fraction::operator>(const Fraction &rhs) const {
  return numerator * rhs.denominator > rhs.numerator * denominator;
}
bool Fraction::operator>=(const Fraction &rhs) const {
  return numerator * rhs.denominator >= rhs.numerator * denominator;
}
bool Fraction::operator==(const Fraction &rhs) const {
  return numerator == rhs.numerator && denominator == rhs.denominator;
}
bool Fraction::operator!=(const Fraction &rhs) const {
  return numerator != rhs.numerator || denominator != rhs.denominator;
}

ostream& operator<<(ostream &out, const Fraction &num) {
  out << num.numerator;
  if (num.denominator == 1) return out;
  else return out << '/' << num.denominator;
}
istream& operator>>(istream &in, Fraction &num) {
  in >> num.numerator >> num.denominator;
  num.simplify();
  return in;
}

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
