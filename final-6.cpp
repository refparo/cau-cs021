//StudybarCommentBegin
#include <iostream>
#include <math.h>

using namespace std;

#define MAX 10

class CPoint {
  int array[MAX][2];
  float sum;

public:
  void CSetPoint();
  void Display();
  void Lenth();
  float Twodist();
};

//StudybarCommentEnd

int sqr(int x) { return x * x; }

void CPoint::CSetPoint() {
  for (int i = 0; i < MAX; i++)
    cin >> array[i][0] >> array[i][1];
}

void CPoint::Display() {
  for (int i = 0; i < MAX; i++)
    cout << '(' << array[i][0] << ',' << array[i][1] << ')' << endl;
}

void CPoint::Lenth() {
  for (int i = 1; i < MAX; i++)
    sum += float(sqrt(double(sqr(array[i][0] - array[i - 1][0])
      + sqr(array[i][1] - array[i - 1][1]))));
  cout << "Length:" << sum << endl;
}

//StudybarCommentBegin
int main() {
    CPoint point;
    point.CSetPoint();
    point.Display();
    point.Lenth();
    return 0;
}

//StudybarCommentEnd
