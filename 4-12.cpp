//StudybarCommentBegin
#include <cctype>
#include <cstdlib>
#include <cstring>
#include <iostream>

using namespace std;

class HugeInt {
  static const int digits = 30;
  short integer[digits];
public:
  HugeInt(long = 0);
  HugeInt(const char *);

  HugeInt operator+(const HugeInt &) const;
  HugeInt operator+(int) const;
  HugeInt operator+(const char *) const;

  int getLength() const;

  friend ostream& operator<<(ostream &, const HugeInt &);
};
//StudybarCommentEnd

#include <iomanip>

HugeInt::HugeInt(long num) {
  int i;
  for (i = 0; i < digits; i++) integer[i] = 0;
  for (i = 0; num > 0; i++) {
    integer[i] = num % 10000;
    num /= 10000;
  }
}
HugeInt::HugeInt(const char* str) {
  int i;
  for (i = 0; i < digits; i++) integer[i] = 0;
  int len = strlen(str);
  for (i = 0; i < len; i++) {
    integer[(len - i - 1) / 4] *= 10;
    integer[(len - i - 1) / 4] += str[i] - '0';
  }
}

HugeInt HugeInt::operator+(const HugeInt &rhs) const {
  HugeInt res;
  short carry = 0;
  for (int i = 0; i < digits; i++) {
    res.integer[i] = integer[i] + rhs.integer[i] + carry;
    carry = res.integer[i] / 10000;
    res.integer[i] %= 10000;
  }
  return res;
}
HugeInt HugeInt::operator+(int rhs) const {
  return *this + HugeInt(rhs);
}
HugeInt HugeInt::operator+(const char* rhs) const {
  return *this + HugeInt(rhs);
}

int HugeInt::getLength() const {
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

ostream& operator<<(ostream &out, const HugeInt &num) {
  int i = HugeInt::digits - 1;
  while (i >= 0 && num.integer[i] == 0) i--;
  if (i == -1) out << '0';
  else {
    out << num.integer[i];
    for (i--; i >= 0; i--) out << setfill('0') << setw(4) << num.integer[i];
  }
  return out;
}

//StudybarCommentBegin
int main() {
  HugeInt n1(7654321);
  HugeInt n2(7891234);
  HugeInt n3("99999999999999999999999999999");
  HugeInt n4("1");
  HugeInt result;

  cout << "n1 is " << n1
    << "\nn2 is " << n2
    << "\nn3 is " << n3
    << "\nn4 is " << n4
    << "\nresult is " << result << "\n\n";

  result = n1 + n2;
  cout << n1 << " + " << n2 << " = " << result << "\n\n";

  cout << n3 << " + " << n4 << "\n= " << (n3 + n4) << "\n\n";

  result = n1 + 9;
  cout << n1 << " + " << 9 << " = " << result << endl;

  result = n2 + "10000";
  cout << n2 << " + " << "10000" << " = " << result << endl;
  return 0;
}
//StudybarCommentEnd
