#include <cmath>
#include <cstdio>
#include <iostream>

using namespace std;

class CEquation {
  virtual double fun(double x) = 0;
public:
  double bisectionSolve(double l, double r) {
    double mid;
    if (fun(l) * fun(r) > 0) {
      printf("error");
      return 0;
    }
    while (fabs(r - l) > 0.000001) {
      mid = (r + l) / 2;
      if (fun(l) * fun(mid) < 0) {
        r = mid;
      } else {
        l = mid;
      }
    }
    return l;
  }
};

//StudybarCommentBegin
class newEquation : public CEquation {
  virtual double fun(double x) {
    return x * x * x * x * x * x - 20 * x * x - 1;
  }
};

double slove(CEquation *pbase) { return pbase->bisectionSolve(0, 10); }

int main(int argc, char *argv[]) {
  newEquation b;
  cout << slove(&b) << endl;
  return 0;
}
//StudybarCommentEnd
