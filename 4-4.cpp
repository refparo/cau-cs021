#include <cmath>
#include <iomanip>
#include <iostream>

#define EPSILON (1e-7)

using namespace std;

class Complex {
  double real, imag;

public:
  Complex(double x = 0, double y = 0) {
    real = x;
    imag = y;
  }

  double getx() const { return real; }
  double gety() const { return imag; }

  bool isReal() const { return abs(imag) < EPSILON; }

  Complex operator+(const Complex &rhs) const {
    return Complex(real + rhs.real, imag + rhs.imag);
  }
  Complex operator-() const {
    return Complex(-real, -imag);
  }
  Complex operator-(const Complex &rhs) const {
    return *this + (-rhs);
  }
  Complex operator*(const double rhs) const {
    return Complex(real * rhs, imag * rhs);
  }
  Complex operator*(const Complex &rhs) const {
    // (a + bi) * (c + di) = (ac - bd + (ad + bc)i)
    return Complex(
      real * rhs.real - imag * rhs.imag,
      real * rhs.imag + imag * rhs.real);
  }
  Complex operator/(const double rhs) const {
    return Complex(real / rhs, imag / rhs);
  }
  Complex operator/(const Complex &rhs) const {
    double sqr_abs = rhs.real * rhs.real + rhs.imag * rhs.imag;
    return Complex(
      (real * rhs.real + imag * rhs.imag) / sqr_abs,
      (imag * rhs.real - real * rhs.imag) / sqr_abs);
  }
  // conjugate
  Complex operator~() const {
    return Complex(real, -imag);
  }
  Complex sqrt() const {
    double abs_num = abs(*this);
    return Complex(
      ::sqrt((abs_num + real) / 2),
      copysign(::sqrt((abs_num - real) / 2), imag));
  }

  void Show() const {
    cout << *this << endl;
  }

  friend Complex operator+(double lhs, const Complex &rhs) {
    return Complex(lhs + rhs.real, rhs.imag);
  }
  friend Complex operator*(double lhs, const Complex &rhs) {
    return Complex(lhs * rhs.real, lhs * rhs.imag);
  }

  friend double abs(const Complex &num) {
    return ::sqrt(num.real * num.real + num.imag * num.imag);
  }
  friend Complex sqrt(const Complex &num) {
    return num.sqrt();
  }

  friend ostream& operator<<(ostream &out, const Complex &num) {
    return out << num.getx() << ' ' << num.gety();
  }
  friend istream& operator>>(istream &in, Complex &num) {
    return in >> num.real >> num.imag;
  }
};

int main() {
  // y=ax²+bx+c
  // |y1|   |1 x1 x1²| |c|
  // |y2| = |1 x2 x2²| |b|
  // |y3|   |1 x3 x3²| |a|
  // A^-1 = A*/det(A)
  // A*[i,j] = A[j,i]
  Complex x1, y1, x2, y2, x3, y3;
  cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3;
  Complex det = (x3 - x2) * (x3 - x1) * (x2 - x1);
  Complex c = (x2 * (x3 - x2) * x3 * y1
    - x1 * (x3 - x1) * x3 * y2
    + x1 * (x2 - x1) * x2 * y3) / det;
  Complex b = (-(x3 * x3 - x2 * x2) * y1
    + (x3 * x3 - x1 * x1) * y2
    - (x2 * x2 - x1 * x1) * y3) / det;
  Complex a = ((x3 - x2) * y1 - (x3 - x1) * y2 + (x2 - x1) * y3) / det;
  cout << fixed << setprecision(6)
    << a << '\n' << b << '\n' << c << endl;
  return 0;
}
