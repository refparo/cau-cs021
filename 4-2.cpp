//StudybarCommentBegin
#include <iomanip>
#include <iostream>
//StudybarCommentEnd
#include <cmath>

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
    out << fixed << setprecision(2);
    if (abs(num.imag) < EPSILON) out << num.real;
    else out
      << noshowpos << num.real
      << showpos << num.imag
      << "i";
    return out;
  }
  friend istream& operator>>(istream &in, ComplexNumber &num) {
    char sign;
    in >> num.real;
    num.imag = 0;
    if (in.eof()) return in;
    sign = char(in.peek());
    if (sign == '+' || sign == '-')
      in >> num.imag >> sign; // asserts sign == 'i'
    else if (sign == 'i') {
      in >> sign;
      num.imag = num.real;
      num.real = 0;
    }
    return in;
  }
};

//StudybarCommentBegin
int main() {
  ComplexNumber cn1, cn2;
  cin >> cn1 >> cn2;
  cout << cn1 + cn2 << endl;
  cout << cn1 - cn2 << endl;
  cout << cn1 * cn2 << endl;
  cout << cn1 / cn2 << endl;
}
//StudybarCommentEnd
