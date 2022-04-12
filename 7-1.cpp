#include <iostream>

using namespace std;

#define PI 3.1415926

class Point {
  double x, y;
public:
  void SetPoint(double x = 0, double y = 0) {
    this->x = x; this->y = y;
  }
};

class Circle : public Point {
  double radius;
public:
  void setRadius(double radius) {
    this->radius = radius;
  }
  double getArea() const {
    return PI * (radius * radius);
  }
};
