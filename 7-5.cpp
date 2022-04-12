//StudybarCommentBegin
#include <cmath>
#include <iostream>

using namespace std;

class Point {
protected:
  double x, y;
public:
  double GetX() const { return x; }
  double GetY() const { return y; }

  double Dist(const Point &rhs) const {
    double dx = x - rhs.x, dy = y - rhs.y;
    return sqrt(dx * dx + dy * dy);
  }

  void SetPoint(double x = 0, double y = 0) {
    this->x = x; this->y = y;
  }
  void Move(double x, double y) {
    this->x += x; this->y += y;
  }
};

class Rectangle : public Point {
protected:
  double w, h;
public:
  double GetW() const { return w; }
  double GetH() const { return h; }

  double DistOfTwoR(const Rectangle &rhs) const {
    return this->Dist(rhs);
  }

  void SetRect(double x, double y, double w, double h) {
    this->SetPoint(x, y);
    this->w = w; this->h = h;
  }
};
//StudybarCommentEnd

Point operator-(const Point &lhs, const Point &rhs) {
  Point res;
  res.SetPoint(lhs.GetX() - rhs.GetX(), lhs.GetY() - rhs.GetY());
  return res;
}

#define PI 3.1415926

Point rotate(const Point &p, double angle) {
  // mat = [cosθ sinθ; -sinθ cosθ]
  // res = mat * p
  angle = angle * PI / 180;
  Point res;
  res.SetPoint(
    p.GetX() * cos(angle) - p.GetY() * sin(angle),
    p.GetX() * sin(angle) + p.GetY() * cos(angle));
  return res;
}

class RectWithAngle : public Rectangle {
  double angle;
public:
  RectWithAngle(double x, double y, double w, double h, double angle)
    : angle(angle) { this->SetRect(x, y, w, h); }

  bool IsPointInMe(const Point &rhs) const {
    Point tmp = rotate(rhs - *this, -angle);
    return tmp.GetX() >= 0 && tmp.GetX() <= w
      && tmp.GetY() >= 0 && tmp.GetY() <= h;
    //&& tmp.GetY() <= 0 && tmp.GetY() >= -h;
  }
};

//StudybarCommentBegin
int main() {
  double angle;
  cin >> angle;
  RectWithAngle R1(2, 3, 3, 4, angle);
  R1.Move(1, 1);
  Point p;
  p.SetPoint(4.5, 4);
  cout << R1.IsPointInMe(p);
  return 0;
}
//StudybarCommentEnd
