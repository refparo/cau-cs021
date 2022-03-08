#include <iostream>

using namespace std;

class Date {
  int m, d, y;
public:
  Date(int month, int day, int year) {
    m = month; d = day; y = year;
  }
  int getMonth() const { return m; }
  void setMonth(int month) {
    if (month > 0 && month <= 12) m = month;
    else m = 1;
  }
  int getDay() const { return d; }
  void setDay(int day) { d = day; }
  int getYear() const { return y; }
  void setYear(int year) { y = year; }
  void displayDate() const {
    cout << m << '/' << d << '/' << y << '\n';
  }
};

//StudybarCommentBegin
int main()
{
    Date date(5, 6, 1981);

    cout << "Month: " << date.getMonth() << endl;
    cout << "Day: " << date.getDay() << endl;
    cout << "Year: " << date.getYear() << endl;
    
    cout << "\nOriginal date:" << endl;
    date.displayDate();

    date.setMonth(13);
    date.setDay(1);
    date.setYear(2005);
    
    cout << "\nNew date:" << endl;
    date.displayDate();
    return 0;
}
//StudybarCommentEnd
