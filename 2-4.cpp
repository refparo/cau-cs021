//StudybarCommentBegin
#include <iostream>
using namespace std;

void swap(int &, int &);

int main() {
  int i, j;
  cin >> i >> j;
  swap(i, j);
  cout << i << " " << j << endl;
  return 0;
}
//StudybarCommentEnd

void swap(int &a, int &b) {
  int tmp = a;
  a = b;
  b = tmp;
}
