#include <iostream>

using namespace std;

class Cmytime {
  int h, m, s;
public:
  Cmytime(int hour = 0, int minute = 0, int second = 0) {
    this->Set(hour, minute, second);
  }
  int Set(int hour, int minute, int second) {
    if (hour >= 0 && hour <= 23
      && minute >= 0 && minute <= 59
      && second >= 0 && second <= 59) {
      h = hour;
      m = minute;
      s = second;
      return 1;
    } else {
      return 0;
    }
  }
  void AddOneSecond() {
    this->AddNSeconds(1);
  }
  int AddNSeconds(int n) {
    s += n % 60;
    m += s / 60;
    s %= 60;
    n /= 60;

    m += n % 60;
    h += m / 60;
    m %= 60;
    n /= 60;

    h += n;
    int d = h / 24;
    h %= 24;
    return d;
  }
  void Show() {
    cout << h << ':' << m << ':' << s;
  }
};

//StudybarCommentBegin
int main() {
  int h, m, s;
  cin >> h >> m >> s;

  Cmytime t1(3, 2, 1);
  t1.Set(h, m, s);
  t1.Show();
  cout << endl << t1.Set(24, 0, 0) << "\n";
  t1.Show();

   t1.AddNSeconds(1);
   cout << endl;
   t1.Show();
   cout << endl << t1.AddNSeconds(3600*25);

  return 0;
}
//StudybarCommentEnd
