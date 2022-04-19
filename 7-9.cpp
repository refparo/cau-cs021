#include <iostream>
#include <ostream>

#define PI 3.14159

using namespace std;

class Shape {
  virtual ostream& print(ostream &out) const = 0;
protected:
  double x, y;
public:
  virtual ~Shape() {}
  inline friend ostream& operator<<(ostream &out, const Shape &self) {
    return self.print(out);
  }
};

class TwoDimensionalShape : public Shape {
public:
  virtual double getArea() = 0;
};

class Square : public TwoDimensionalShape {
  double a;
  ostream& print(ostream &out) const {
    return out << "Square with side length " << a
      << "; center at (" << x << ", " << y << ")";
  }
public:
  Square(double a, double x = 0, double y = 0) : a(a) {
    this->x = x; this->y = y;
  }
  double getArea() {
    return a * a;
  }
};

class Circle : public TwoDimensionalShape {
  double r;
  ostream& print(ostream &out) const {
    return out << "Circle with radius " << r
      << "; center at (" << x << ", " << y << ")";
  }
public:
  Circle(double r, double x = 0, double y = 0) : r(r) {
    this->x = x; this->y = y;
  }
  double getArea() {
    return PI * r * r;
  }
};

class ThreeDimensionalShape : public Shape {
public:
  virtual double getArea() = 0;
  virtual double getVolume() = 0;
};

class Cube : public ThreeDimensionalShape {
  double a;
  ostream& print(ostream &out) const {
    return out << "Cube with side length " << a
      << "; center at (" << x << ", " << y << ")";
  }
public:
  Cube(double a, double x = 0, double y = 0) : a(a) {
    this->x = x; this->y = y;
  }
  double getArea() {
    return 6 * a * a;
  }
  double getVolume() {
    return a * a * a;
  }
};

class Sphere : public ThreeDimensionalShape {
  double r;
  ostream& print(ostream &out) const {
    return out << "Sphere with radius " << r
      << "; center at (" << x << ", " << y << ")";
  }
public:
  Sphere(double r, double x = 0, double y = 0) : r(r) {
    this->x = x; this->y = y;
  }
  double getArea() {
    return 4 * PI * r * r;
  }
  double getVolume() {
    return 4 * PI * r * r * r / 3;
  }
};

//StudybarCommentBegin
int main() {
  Shape *shapes[4];

  shapes[0] = new Circle(3.5, 6, 9);
  shapes[1] = new Square(12, 2, 2);
  shapes[2] = new Sphere(5, 1.5, 4.5);
  shapes[3] = new Cube(2.2);

  for (int i = 0; i < 4; i++) {
    cout << *(shapes[i]) << endl;

    TwoDimensionalShape *twoDimensionalShapePtr =
      dynamic_cast<TwoDimensionalShape *>(shapes[i]);

    if (twoDimensionalShapePtr != 0)
      cout << "Area: " << twoDimensionalShapePtr->getArea() << endl;

    ThreeDimensionalShape *threeDimensionalShapePtr =
      dynamic_cast<ThreeDimensionalShape *>(shapes[i]);

    if (threeDimensionalShapePtr != 0)
      cout << "Area: " << threeDimensionalShapePtr->getArea()
        << "\nVolume: " << threeDimensionalShapePtr->getVolume() << endl;

    cout << endl;
  }

  return 0;
}
//StudybarCommentEnd
