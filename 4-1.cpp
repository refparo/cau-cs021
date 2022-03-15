#include <cmath>
#include <iomanip>
#include <iostream>

#define EPSILON (1e-7)

using namespace std;

// strangely, this function isn't available in the OJ
template<typename T>
T copysign(T to, T from) {
  if (from * to < 0) return -to;
  else return to;
}

class ComplexNumber {
  double real, imag;

public:
  ComplexNumber(double x = 0, double y = 0) {
    real = x;
    imag = y;
  }

  double GetReal() const { return real; }
  double GetImaginary() const { return imag; }
  void Set(double x, double y) {
    real = x;
    imag = y;
  }

  bool IsReal() const { return abs(imag) < EPSILON; }

  ComplexNumber operator+(const ComplexNumber &rhs) const {
    return ComplexNumber(real + rhs.real, imag + rhs.imag);
  }
  ComplexNumber operator-() const {
    return ComplexNumber(-real, -imag);
  }
  ComplexNumber operator-(const ComplexNumber &rhs) const {
    return *this + (-rhs);
  }
  ComplexNumber operator*(const double rhs) const {
    return ComplexNumber(real * rhs, imag * rhs);
  }
  ComplexNumber operator*(const ComplexNumber &rhs) const {
    // (a + bi) * (c + di) = (ac - bd + (ad + bc)i)
    return ComplexNumber(
      real * rhs.real - imag * rhs.imag,
      real * rhs.imag + imag * rhs.real);
  }
  ComplexNumber operator/(const double rhs) const {
    return ComplexNumber(real / rhs, imag / rhs);
  }
  ComplexNumber operator/(const ComplexNumber &rhs) const {
    double sqr_abs = rhs.real * rhs.real + rhs.imag * rhs.imag;
    return ComplexNumber(
      (real * rhs.real + imag * rhs.imag) / sqr_abs,
      (imag * rhs.real - real * rhs.imag) / sqr_abs);
  }
  // conjugate
  ComplexNumber operator~() const {
    return ComplexNumber(real, -imag);
  }
  bool operator==(const ComplexNumber &rhs) const {
    return abs(real - rhs.real) < EPSILON && abs(imag - rhs.imag) < EPSILON;
  }
  bool operator!=(const ComplexNumber &rhs) const {
    return abs(real - rhs.real) >= EPSILON || abs(imag - rhs.imag) >= EPSILON;
  }
  ComplexNumber sqrt() const {
    double abs_num = abs(*this);
    return ComplexNumber(
      ::sqrt((abs_num + real) / 2),
      copysign(::sqrt((abs_num - real) / 2), imag));
  }

  void Show() const {
    cout // << fixed << setprecision(2)
      << *this;
  }

  friend ComplexNumber operator+(double lhs, const ComplexNumber &rhs) {
    return ComplexNumber(lhs + rhs.real, rhs.imag);
  }

  friend double abs(const ComplexNumber &num) {
    return ::sqrt(num.real * num.real + num.imag * num.imag);
  }
  friend ComplexNumber sqrt(const ComplexNumber &num) {
    return num.sqrt();
  }

  friend ostream& operator<<(ostream &out, const ComplexNumber &num) {
    ios fmt(NULL); // nullptr isn't available in the OJ
    fmt.copyfmt(out);
    out << '('
      << num.GetReal()
      << showpos << num.GetImaginary()
      << "i)";
    out.copyfmt(fmt);
    return out;
  }
  friend istream& operator>>(istream &in, ComplexNumber &num) {
    return in >> num.real >> num.imag;
  }
};

//StudybarCommentBegin
int main() {
  ComplexNumber z1(3, 4), z2(7), z3;
  double x, y;
  cin >> x >> y;
  z2.Set(x, y);
  z3 = z1 + z2;
  cout << "\n";
  z3.Show();
  z3 = z1 - z2;
  cout << "\n";
  z3.Show();
  z3 = z1 * z2;
  cout << "\n";
  z3.Show();
}
//StudybarCommentEnd
