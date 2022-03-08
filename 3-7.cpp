#include <cmath>
#include <iostream>

using namespace std;

class Rectangle {
  double vert[4][2], x, y;
public:
  Rectangle(double vertices[4][2]) {
    for (int i = 0; i < 4; i++)
      for (int j = 0; j < 2; j++)
        if (vertices[i][j] >= 0 && vertices[i][j] < 20) vert[i][j] = vertices[i][j];
        else {
          cout << "第" << i + 1 << "个点的" << (j == 0 ? "横" : "纵")
            << "坐标值无效,被置为0\n";
          vert[i][j] = 0;
        }
    if (!(vert[0][1] == vert[1][1] && vert[2][1] == vert[3][1]
      && vert[0][0] == vert[2][0] && vert[1][0] == vert[3][0])) {
      cout << "不能构成长方形！" << endl;
      exit(1);
    }
    x = abs(vert[0][0] - vert[1][0]);
    y = vert[0][1] - vert[2][1];
  }
  double length() const { return max(x, y); }
  double width() const { return min(x, y); }
  double perimeter() const { return 2 * (x + y); }
  double area() const { return x * y; }
  bool square() const { return x == y; }
};

//StudybarCommentBegin
int main() {
  double rect[4][2];
  int i;

  for (i = 0; i < 4; i++)
    cin >> rect[i][0] >> rect[i][1];

  Rectangle myRect(rect);
  cout << "长度为：" << myRect.length() << endl;
  cout << "宽度为：" << myRect.width() << endl;
  cout << "周长为：" << myRect.perimeter() << endl;
  cout << "面积为：" << myRect.area() << endl;

  if (myRect.square()) cout << "此长方形是一个正方形" << endl;
  else cout << "此长方形不是一个正方形" << endl;

  return 0;
}
//StudybarCommentEnd
