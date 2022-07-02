//StudybarCommentBegin
#include <iostream>
#include <iomanip>

using std::cin;
using std::cout;
using std::endl;
using std::setfill;
using std::setw;
//StudybarCommentEnd

class Time {
  int h, m, s;
public:
  Time(int hour = 0, int minute = 0, int second = 0)
    : h(hour), m(minute), s(second) {}
  void setTime(int hour, int minute, int second) {
    h = hour; m = minute; s = second;
  }
  void printTime() const {
    cout << setfill('0')
      << setw(2) << h << ":"
      << setw(2) << m << ":"
      << setw(2) << s << endl;
  }
  Time& operator++() {
    return *this = *this + 1;
  }
  Time operator++(int) {
    Time res(*this);
    *this = *this + 1;
    return res;
  }
  Time& operator--() {
    return *this = *this - 1;
  }
  Time operator--(int) {
    Time res(*this);
    *this = *this - 1;
    return res;
  }

  Time operator+(int n) const {
    Time res(h, m, s);
    res.s += n % 60;
    res.m += res.s / 60;
    res.s %= 60;
    n /= 60;
    if (res.s < 0) {
      res.s += 60;
      res.m--;
    }

    res.m += n % 60;
    res.h += res.m / 60;
    res.m %= 60;
    n /= 60;
    if (res.m < 0) {
      res.m += 60;
      res.h--;
    }

    res.h += n;
    res.h %= 24;
    if (res.h < 0) res.h += 24;
    return res;
  }

  Time operator-(int n) const {
    return *this + (-n);
  }
};

//StudybarCommentBegin
int main() {
  int hour, minute, second;
  int number;
  Time t1(23, 45, 0), t2, t3(t1), t4;
  cin >> hour >> minute >> second >> number;
  t1.setTime(hour, minute, second);
  t2 = t1--;
  t2.printTime();
  t1.printTime();
  t3 = --t1;
  t3.printTime();
  t4 = t1 - number;
  t4.printTime();
}
//StudybarCommentEnd
