#include <iostream>

using namespace std;

template<typename T>
T maximum(T i, T j, T k) {
  if (i >= j && i >= k) return i;
  else if (j >= i && j >= k) return j;
  else return k;
}

template<typename T>
T maxinum(T i, T j, T k) {
  return maximum(i, j, k);
}

//StudybarCommentBegin
int main() {
  int b1, b2, b3;
  float c1, c2, c3;
  char a1, a2, a3;
  cin >> b1 >> b2 >> b3 >> c1 >> c2 >> c3>> a1 >> a2 >> a3;
  cout << maxinum(b1, b2, b3)
    << ' ' << maxinum(c1, c2, c3)
    << ' ' << maxinum(a1, a2, a3);
	return 0;
}
//StudybarCommentEnd
