//StudybarCommentBegin
#include <iostream>
#include <iterator>

using namespace std;

class MyLess {
public:
  bool operator()(int a1, int a2) {
    if ((a1 % 10) < (a2 % 10))
      return true;
    else
      return false;
  }
};

bool MyCompare(int a1, int a2) {
  if ((a1 % 10) < (a2 % 10))
    return false;
  else
    return true;
}
//StudybarCommentEnd

template<typename I, typename F>
I MyMax(I begin, I end, F greater) {
  I max = begin;
  for (I p = begin + 1; p != end; p++)
    if (greater(*max, *p)) max = p;
  return max;
}

//StudybarCommentBegin
int main() {
  int a[] = {35, 7, 13, 19, 12};
  cout << *MyMax(a, a + 5, MyLess()) << endl;
  cout << *MyMax(a, a + 5, MyCompare) << endl;
  return 0;
}
//StudybarCommentEnd
