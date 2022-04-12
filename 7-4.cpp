#include <cmath>
#include <iostream>

using namespace std;

#define PI 3.1415926

class Point {
protected:
  double x, y;
public:
  double GetX() const { return x; }
  double GetY() const { return y; }

  void SetPoint(double x = 0, double y = 0) {
    this->x = x; this->y = y;
  }
  void Move(double x, double y) {
    this->x += x; this->y += y;
  }
};

class Rectangle : public Point {
  double w, h;
public:
  double GetW() const { return w; }
  double GetH() const { return h; }

  double DistOfTwoR(const Rectangle &rhs) const {
    double dx = x - rhs.x, dy = y - rhs.y;
    return sqrt(dx * dx + dy * dy);
  }

  void SetRect(double x, double y, double w, double h) {
    this->SetPoint(x, y);
    this->w = w; this->h = h;
  }
};
