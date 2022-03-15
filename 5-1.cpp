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
  Time operator++() {
    *this = 1 + *this;
    return *this;
  }
  Time operator--() {
    *this = -1 + *this;
    return *this;
  }
  Time operator--(int) {
    *this = -1 + *this;
    return 1 + *this;
  }

  friend Time operator+(int n, const Time &time) {
    int h = time.h, m = time.m, s = time.s;
    s += n % 60;
    m += s / 60;
    s %= 60;
    n /= 60;
    if (s < 0) {
      s += 60;
      m--;
    }

    m += n % 60;
    h += m / 60;
    m %= 60;
    n /= 60;
    if (m < 0) {
      m += 60;
      h--;
    }

    h += n;
    h %= 24;
    if (h < 0) h += 24;
    return Time(h, m, s);
  }
};

//StudybarCommentBegin
int main() {
  int hour, minute, second;
  int increase;
  Time t1(23, 45, 0), t2, t3(t1), t4;
  cin >> hour >> minute >> second >> increase;
  t1.setTime(hour, minute, second);
  t1.printTime();
  t2 = ++t1;
  t2.printTime();
  t3 = increase + t1;
  t3.printTime();
  t1.setTime(hour, minute, second);
  t2 = t1--;
  t2.printTime();
  t1.printTime();
  t3 = --t1;
  t3.printTime();
  t4 = increase + t1;
  t4.printTime();
  return 0;
}
//StudybarCommentEnd
