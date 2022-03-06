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

  double getReal() const { return real; }
  double getImag() const { return imag; }

  bool isReal() const { return fabs(imag) < EPSILON; }

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

  friend double abs(const Complex &num) {
    return sqrt(num.real * num.real + num.imag * num.imag);
  }
  friend Complex sqrt(const Complex &num) {
    double abs_num = abs(num);
    return Complex(
      sqrt((abs_num + num.real) / 2),
      copysign(sqrt((abs_num - num.real) / 2), num.imag));
  }

  friend ostream& operator<<(ostream &out, const Complex &num) {
    ios fmt(nullptr);
    fmt.copyfmt(out);
    out << fixed << setprecision(2) << '('
      << num.getReal()
      << showpos << num.getImag()
      << "i)";
    out.copyfmt(fmt);
    return out;
  }
  friend istream& operator>>(istream &in, Complex &num) {
    return in >> num.real >> num.imag;
  }
};

int main() {
  Complex a, b, c;
  cin >> a >> b >> c;
  // Δ = b²-4ac
  Complex sqrt_delta = sqrt(b * b - a * c * 4);
  Complex root1 = (-b + sqrt_delta) / (a * 2);
  Complex root2 = (-b - sqrt_delta) / (a * 2);
  if (root1.getImag() > 0) cout << root1 << '\n' << root2 << endl;
  else cout << root2 << '\n' << root1 << endl;
  return 0;
}
