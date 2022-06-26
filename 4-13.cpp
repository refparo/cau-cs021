#include <cstring>
#include <iomanip>
#include <iostream>

using namespace std;

inline int ceil_div(int a, int b) {
  return a % b == 0 ? a / b : a / b + 1;
}

class HugeInt {
  static const int digits = 30000;
  short integer[digits];
public:
  HugeInt(long num = 0) {
    int i = 0;
    for (i = 0; i < digits; i++) integer[i] = 0;
    i = 0;
    while (num > 0) {
      integer[i] = num % 10000;
      num /= 10000;
      i++;
    }
  }
  HugeInt(const char* str) {
    int i;
    for (i = 0; i < digits; i++) integer[i] = 0;
    int len = strlen(str);
    for (i = 0; i < len; i++) {
      integer[(len - i - 1) / 4] *= 10;
      integer[(len - i - 1) / 4] += str[i] - '0';
    }
  }

  HugeInt& operator+=(const HugeInt &rhs) {
    short carry = 0;
    for (int i = 0; i < digits; i++) {
      integer[i] += rhs.integer[i] + carry;
      carry = integer[i] / 10000;
      integer[i] %= 10000;
    }
    return *this;
  }
  HugeInt operator+(const HugeInt &rhs) const {
    HugeInt res;
    short carry = 0;
    for (int i = 0; i < digits; i++) {
      res.integer[i] = integer[i] + rhs.integer[i] + carry;
      carry = res.integer[i] / 10000;
      res.integer[i] %= 10000;
    }
    return res;
  }
  HugeInt operator+(int rhs) const {
    return *this + HugeInt(rhs);
  }
  HugeInt operator+(const char* rhs) const {
    return *this + HugeInt(rhs);
  }

  HugeInt operator-(const HugeInt &rhs) const {
    HugeInt res;
    for (int i = 0; i < digits; i++) {
      res.integer[i] += integer[i] - rhs.integer[i];
      if (res.integer[i] < 0) {
        res.integer[i] += 10000;
        res.integer[i + 1]--; // ignore the case when lhs < rhs
      }
    }
    return res;
  }
  HugeInt operator*(const HugeInt &rhs) const {
    HugeInt res;
    int lenL = getInnerLength(), lenR = rhs.getInnerLength();
    int tmp;
    for (int i = 0; i < lenL; i++)
      if (integer[i] != 0) for (int j = 0; j < lenR; j++) {
        tmp = int(integer[i]) * rhs.integer[j];
        res.integer[i + j + 1] += tmp / 10000;
        res.integer[i + j] += tmp % 10000;
      }
    return res;
  }
  HugeInt operator/(const HugeInt &rhs) const {
    HugeInt res;
    int lenL = getLength(), lenR = rhs.getLength();
    if (lenL < lenR) return res;
    lenL = ceil_div(lenL, 4); lenR = ceil_div(lenR, 4);
    int lenRes = lenL - lenR;
    HugeInt rem;
    for (int i = 0; i < lenR - 1; i++)
      rem.integer[lenR - 2 - i] = integer[lenL - 1 - i];
    for (int i = lenRes; i >= 0; i--) {
      rem = HugeInt(10000) * rem + HugeInt(integer[i]);
      short digit = 0;
      while (rem >= rhs) {
        digit++;
        rem -= rhs;
      }
      res.integer[i] = digit;
    }
    return res;
  }

  HugeInt& operator-=(const HugeInt &rhs) {
    for (int i = 0; i < digits; i++) {
      integer[i] -= rhs.integer[i];
      if (integer[i] < 0) {
        integer[i] += 10000;
        integer[i + 1]--; // ignore the case when lhs < rhs
      }
    }
    return *this;
  }

  #define INEQUALITY(N, A, B, C) \
    bool N(const HugeInt &rhs) const { \
      for (int i = digits - 1; i >= 0; i--) \
        if (integer[i] A rhs.integer[i]) return true; \
        else if (integer[i] B rhs.integer[i]) return false; \
      return C; \
    }
  INEQUALITY(operator>, >, <, false)
  INEQUALITY(operator>=, >, <, true)
  INEQUALITY(operator<, <, >, false)
  INEQUALITY(operator<=, <, >, true)
  #undef INEQUALITY
  bool operator==(const HugeInt &rhs) const {
    for (int i = digits - 1; i >= 0; i--)
      if (integer[i] != rhs.integer[i]) return false;
    return true;
  }
  bool operator!=(const HugeInt &rhs) const {
    return !(*this == rhs);
  }

  int getInnerLength() const {
    int len = digits;
    while (integer[len - 1] == 0) len--;
    return len;
  }
  int getLength() const {
    int len = 0;
    int i = digits - 1;
    while (i >= 0 && integer[i] == 0) i--;
    if (i >= 0) {
      short temp = integer[i];
      while (temp > 0) {
        len++;
        temp /= 10;
      }
    }
    len += i * 4;
    return len;
  }

  friend ostream& operator<<(ostream &out, const HugeInt &num) {
    int i = HugeInt::digits - 1;
    while (i >= 0 && num.integer[i] == 0) i--;
    if (i == -1) out << '0';
    else {
      out << num.integer[i];
      for (i--; i >= 0; i--) out << setfill('0') << setw(4) << num.integer[i];
    }
    return out;
  }
};

/*
//StudybarCommentBegin
int main() {
  HugeInt n1(7654321);
  HugeInt n2(7891234);
  HugeInt n3("99999999999999999999999999999");
  HugeInt n4("1");
  HugeInt n5("12341234");
  HugeInt n6("7888");
  HugeInt result;

  cout << "n1 is " << n1
    << "\nn2 is " << n2
    << "\nn3 is " << n3
    << "\nn4 is " << n4
    << "\nn5 is " << n5
    << "\nn6 is " << n6
    << "\nresult is " << result << "\n\n";

  if (n1 == n2)
    cout << "n1 equals n2" << endl;

  if (n1 != n2)
    cout << "n1 is not equal to n2" << endl;

  if (n1 < n2)
    cout << "n1 is less than n2" << endl;

  if (n1 <= n2)
    cout << "n1 is less than or equal to n2" << endl;

  if (n1 > n2)
    cout << "n1 is greater than n2" << endl;

  if (n1 >= n2)
    cout << "n1 is greater than or equal to n2" << endl;

  result = n1 + n2;
  cout << n1 << " + " << n2 << " = " << result << "\n\n";

  cout << n3 << " + " << n4 << "\n= " << (n3 + n4) << "\n\n";

  result = n1 + 9;
  cout << n1 << " + " << 9 << " = " << result << endl;

  result = n2 + "10000";
  cout << n2 << " + " << "10000" << " = " << result << endl;

  result = n5 * n6;
  cout << n5 << " * " << n6 << " = " << result << endl;
  
  result = n5 - n6;
  cout << n5 << " - " << n6 << " = " << result << endl;
  
  result = n5 / n6;
  cout << n5 << " / " << n6 << " = " << result << endl;

  return 0;
}
//StudybarCommentEnd
*/

int main() {
  HugeInt a(1), b(999999999);
  for (int i = 0; i < 1000; i++) a = a * b;
  cout << a << endl;
  return 0;
}
