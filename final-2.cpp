//StudybarCommentBegin
#include <iostream>

using namespace std;

class Shape {
  static int count;

public:
  Shape() {
    Shape::count++;
    cout << "The current number of Shapes is " << Shape::count << endl;
  }
  virtual ~Shape() {
    cout << "~Shape() is called. ";
    cout << "The current number of Shapes is " << --Shape::count << endl;
  }
  virtual float GetPerim() = 0;
};
int Shape::count = 0;
//StudybarCommentEnd

class Rectangle : public Shape {
  float w, h;
public:
  Rectangle(float w, float h) : w(w), h(h) {}
  ~Rectangle() {
    cout << "~Rectangle() is called" << endl;
  }
  float GetPerim() {
    return 2 * (w + h);
  }
};

const float PI = 3.14;

class Circle : public Shape {
  float r;
public:
  Circle(float r) : r(r) {}
  ~Circle() {
    cout << "~Circle() is called" << endl;
  }
  float GetPerim() {
    return 2 * PI * r;
  }
};

//StudybarCommentBegin
int main() {
  Shape *sp1, *sp2;
  int r, w, h;
  cin >> r;      //请输入一个大于等于0的整数
  cin >> w >> h; //请输入两个个大于等于0的整数

  sp1 = new Circle(r);
  cout << sp1->GetPerim() << endl;
  sp2 = new Rectangle(w, h);
  cout << sp2->GetPerim() << endl;
  delete sp1;  delete sp2;
}
//StudybarCommentEnd
