//StudybarCommentBegin
#include <iostream>
#include <iomanip>
using std::cin;
using std::cout;
using std::endl;
using std::setfill;
using std::setw;
//StudybarCommentEnd

const int months[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

constexpr int get_month(int year, int month) {
  return month == 2 && year % 4 == 0 && (year % 100 != 0 || year % 400 == 0)
    ? 29 : months[month];
}

class Date {
  int y, m, d;
public:
  Date(int year = 1, int month = 1, int day = 1)
    : y(year), m(month), d(day) {}
  int year() const { return y; }
  int month() const { return m; }
  int day() const { return d; }
  void setDate(int year, int month, int day) {
    y = year; m = month; d = day;
  }
  void printDate() const {
    cout << y << "/" << m << "/" << d;
  }
  Date operator++(int) {
    Date temp(*this);
    if (d == get_month(y, m)) { d = 1; m++; }
    else d++;
    if (m > 12) { m = 1; y++; }
    return temp;
  }
  void operator+=(int day) {
    d += day;
    int month;
    while (d > (month = get_month(y, m))) {
      d -= month;
      m++;
      if (m > 12) { m = 1; y++; }
    }
    while (d <= 0) {
      m--;
      if (m < 1) { m = 12; y--; }
      d += get_month(y, m);
    }
  }
  void operator-=(int day) {
    *this += -day;
  }
  int operator-(const Date &rhs) const {
    if (*this < rhs) return -(rhs - *this);
    Date temp(rhs);
    int day = 0;
    if (temp.y < y || (temp.y == y && temp.m < m)) {
      day += 1 + get_month(temp.y, temp.m) - temp.d;
      temp.d = 1;
      temp.m++;
      if (temp.m > 12) {
        temp.m = 1;
        temp.y++;
      }
    }
    while (temp.y < y || (temp.y == y && temp.m < m)) {
      day += get_month(temp.y, temp.m);
      temp.m++;
      if (temp.m > 12) {
        temp.m = 1;
        temp.y++;
      }
    }
    day += d - 1;
    return day;
  }
  bool operator<(const Date &rhs) const {
    return y < rhs.y
      || (y == rhs.y && (m < rhs.m || (m == rhs.m && d < rhs.d)));
  }
  bool operator==(const Date &rhs) const {
    return y == rhs.y && m == rhs.m && d == rhs.d;
  }
};

class Daytime {
  int h, m, s;
  int overflow = 0;
public:
  Daytime(int hour = 0, int minute = 0, int second = 0, int overflow = 0)
    : h(hour), m(minute), s(second), overflow(overflow) {}
  int getOverflow() {
    int res = overflow;
    overflow = 0;
    return res;
  }
  void setTime(int hour, int minute, int second) {
    h = hour; m = minute; s = second;
  }
  void printTime() const {
    cout << setfill('0')
      << setw(2) << h << ":"
      << setw(2) << m << ":"
      << setw(2) << s << endl;
  }
  Daytime& operator++() {
    *this = 1 + *this;
    return *this;
  }
  Daytime& operator--() {
    *this = -1 + *this;
    return *this;
  }
  Daytime operator--(int) {
    Daytime res(*this);
    *this = -1 + *this;
    return res;
  }
  int operator-(const Daytime &rhs) const {
    if (*this < rhs) return -(rhs - *this);
    return ((h - rhs.h) * 60 + (m - rhs.m)) * 60 + (s - rhs.s);
  }
  bool operator<(const Daytime &rhs) const {
    return h < rhs.h
      || (h == rhs.h && (m < rhs.m || (m == rhs.m && s < rhs.s)));
  }

  friend Daytime operator+(int n, const Daytime &time) {
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
    int overflow = h / 24;
    h %= 24;
    if (h < 0) {
      h += 24;
      overflow--;
    }
    return Daytime(h, m, s, overflow);
  }
};

class Time {
  Date d;
  Daytime t;
public:
  Time(
    int year = 1, int month = 1, int day = 1,
    int hour = 0, int minute = 0, int second = 0)
    : d(Date(year, month, day)), t(Daytime(hour, minute, second)) {}
  Time(Date date, Daytime daytime): d(date), t(daytime) {}
  void setTime(int year, int month, int day, int hour, int minute, int second) {
    d.setDate(year, month, day);
    t.setTime(hour, minute, second);
  }
  void printTime() const {
    d.printDate();
    cout << ' ';
    t.printTime();
  }
  Time operator++() {
    ++t;
    if (t.getOverflow() > 0) d++;
    return *this;
  }
  Time operator--() {
    --t;
    if (t.getOverflow() < 0) d -= 1;
    return *this;
  }
  Time operator--(int) {
    Time res(*this);
    --*this;
    return res;
  }
  Time operator+(int n) const {
    Daytime newT(n + t);
    Date newD(d);
    newD += newT.getOverflow();
    return Time(newD, newT);
  }
  friend Time operator+(int n, const Time &time) {
    return time + n;
  }
  int operator-(const Time &rhs) const {
    if (*this < rhs) return -(rhs - *this);
    return (d - rhs.d) * 24 * 60 * 60 + (t - rhs.t);
  }
  bool operator<(const Time &rhs) const {
    return d < rhs.d || (d == rhs.d && t < rhs.t);
  }
};

//StudybarCommentBegin
int main() {
  int year, month, day;
  int hour, minute, second;
  int number;
  int capacity = 0;
  Time t1(2016, 3, 31, 23, 45, 0), t2, t3(t1), t4;
  cin >> year >> month >> day >> hour >> minute >> second;
  t1.setTime(year, month, day, hour, minute, second);
  cin >> year >> month >> day >> hour >> minute >> second;
  t2.setTime(year, month, day, hour, minute, second);
  cin >> number;
  cout << endl;
  t3 = t1--;
  t3.printTime();
  t1.printTime();
  t4 = --t1;
  t4.printTime();
  t4 = number + t1;
  t4.printTime();
  capacity = t2 - t1;
  cout << capacity << endl;
}
//StudybarCommentEnd
