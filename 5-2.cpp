#include <iostream>

using namespace std;

const int months[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

constexpr int get_month(int year, int month) {
  return month == 2 && year % 4 == 0 && (year % 100 != 0 || year % 400 == 0)
    ? 29 : months[month];
}

class date {
  int y, m, d;
public:
  date(int year = 1, int month = 1, int day = 1)
    : y(year), m(month), d(day) {}
  int year() const { return y; }
  int month() const { return m; }
  int day() const { return d; }
  date operator++(int) {
    date temp(*this);
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
  int operator-(const date &rhs) const {
    if (y < rhs.y || (y == rhs.y && (m < rhs.m || (m == rhs.m && d < rhs.d))))
      return -(rhs - *this);
    date temp(rhs);
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
};

//StudybarCommentBegin
int main(void) {
  using std::cin;
  using std::cout;
  using std::endl;

  date D1, D2;

  int year;
  int month;
  int day;
  cin >> year >> month >> day;
  D1 = date(year, month, day);
  cin >> year >> month >> day;
  D2 = date(year, month, day);

  cout << D2 - D1 << endl;

  cin >> day;

  D1 += day;
  D2 -= day;
  cout << D1.year() << " " << D1.month() << " " << D1.day() << endl;
  cout << D2.year() << " " << D2.month() << " " << D2.day() << endl;

  return 0;
}
//StudybarCommentEnd
