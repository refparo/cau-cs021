#include <iostream>

using namespace std;

class Point {
public:
  Point(int x = 0, int y = 0) : x(x), y(y) {}
  int getX() const { return this->x; }
  int getY() const { return this->y; }
private:
  int x, y;
};

int main() {
  Point a(4, 5);
  Point const b(6, 7);
  Point const *pa = &a;
  Point const *pb = &b;
  const Point &rb = b;

  cout << pa->getX() << endl;
  cout << a.getY() << endl;
  cout << (*pb).getY() << endl;
  cout << rb.getX() << endl;

  return 0;
}
