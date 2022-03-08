#include <iostream>

using namespace std;

int myadd(int a, int b) { return a + b; }
int myadd(int a, int b, int c) { return a + b + c; }
int myadd(int arr[], int n) {
  int sum = 0;
  for (int i = 0; i < n; i++) sum += arr[i];
  return sum;
}

//StudybarCommentBegin
int main() {
  cout << myadd(2, 3) << "\n";
  cout << myadd(2, 3, 4);
  return 0;
}
//StudybarCommentEnd
