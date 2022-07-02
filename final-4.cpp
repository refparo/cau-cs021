#include <iostream>

using namespace std;

class FiniteField {
  int p, n;
public:
  FiniteField(int p = 3, int n = 0) : p(p), n(n % p) {}
  void Show() const { cout << n; }
  FiniteField operator+(const FiniteField &rhs) const {
    return FiniteField(p, n + rhs.n);
  }
  FiniteField operator-(const FiniteField &rhs) const {
    return FiniteField(p, p + n - rhs.n);
  }
  FiniteField operator*(const FiniteField &rhs) const {
    return FiniteField(p, n * rhs.n);
  }
  FiniteField operator/(const FiniteField &rhs) const {
    int k = 0;
    while ((k * p + 1) % rhs.n != 0) k++;
    return FiniteField(p, n * ((k * p + 1) / rhs.n));
  }
};

//StudybarCommentBegin
int main() {
  int prime, a, b;
  char opt;
  cin >> prime;
  cin >> a >> opt >> b;

  FiniteField f1(prime, a), f2(prime, b), f3;
  switch (opt) {
  case '+':
    f3 = f1 + f2;
    break;
  case '-':
    f3 = f1 - f2;
    break;
  case '*':
    f3 = f1 * f2;
    break;
  case '/':
    f3 = f1 / f2;
    break;
  }
  f3.Show();
}
//StudybarCommentEnd
