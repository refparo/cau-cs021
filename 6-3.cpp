#include <iostream>

using namespace std;

template <typename T>
void printArray(const T *arrayset, int count) {
  for (int i = 0; i < count && arrayset[i] != '\0'; i++)
    cout << arrayset[i] << " ";
  cout << endl;
}

template <typename T>
int printArray(const T *arrayset, int len, int begin, int end) {
  if (begin < 0 || end >= len || begin > end) return 0;
  int i;
  for (i = begin; i <= end && arrayset[i] != '\0'; i++)
    cout << arrayset[i] << " ";
  cout << endl;
  return i - begin;
}

//StudybarCommentBegin
int main() {
  const int aCount = 5;
  const int bCount = 7;
  const int cCount = 6;

  int a[aCount] = {1, 2, 3, 4, 5};
  double b[bCount] = {1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7};
  char c[cCount] = "HELLO";
  int elements;

  cout << "\nUsing original printArray function\n";
  printArray(a, aCount);

  cout << "\nArray a contains:\n";
  elements = printArray(a, aCount, 0, aCount - 1);
  cout << elements << " elements were output\n";

  cout << "Array a from 1 to 3 is:\n";
  elements = printArray(a, aCount, 1, 3);
  cout << elements << " elements were output\n";

  cout << "Array a output with invalid subscripts:\n";
  elements = printArray(a, aCount, -1, 10);
  cout << elements << " elements were output\n\n";

  cout << "\nUsing original printArray function\n";
  printArray(a, aCount);

  cout << "Array b contains:\n";
  elements = printArray(b, bCount, 0, bCount - 1);
  cout << elements << " elements were output\n";

  cout << "Array b from 1 to 3 is:\n";
  elements = printArray(b, bCount, 1, 3);
  cout << elements << " elements were output\n";

  cout << "Array b output with invalid subscripts:\n";
  elements = printArray(b, bCount, -1, 10);
  cout << elements << " elements were output\n\n";

  cout << "\nUsing original printArray function\n";
  printArray(a, aCount);

  cout << "Array c contains:\n";
  elements = printArray(c, cCount, 0, cCount - 1);
  cout << elements << " elements were output\n";

  cout << "Array c from 1 to 3 is:\n";
  elements = printArray(c, cCount, 1, 3);
  cout << elements << " elements were output\n";

  cout << "Array c output with invalid subscripts:\n";
  elements = printArray(c, cCount, -1, 10);
  cout << elements << " elements were output" << endl;

  return 0;
}
//StudybarCommentEnd
