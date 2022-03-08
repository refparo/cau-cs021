#include <iomanip>
#include <iostream>

using namespace std;

class Rectangle {
  double x, y;
public:
  double getLength() const { return x; }
  void setLength(double length) {
    if (length > 0 && length < 20) x = length;
    else x = 1;
  }
  double getWidth() const { return y; }
  void setWidth(double width) {
    if (width > 0 && width < 20) y = width;
    else y = 1;
  }
  double perimeter() const { return 2 * (x + y); }
  double area() const { return x * y; }
};

//StudybarCommentBegin
int main() {
  Rectangle r;
  double length, width;
  cin >> length;
  cin >> width;
  r.setLength(length);
  r.setWidth(width);
  cout << "the perimeter is:"
    << setprecision(2) << fixed << r.perimeter() << endl;
  cout << "the area is:"
    << setprecision(2) << fixed << r.area() << endl;
  return 0;
}
//StudybarCommentEnd
