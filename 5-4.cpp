#include <iomanip>
#include <iostream>

using namespace std;

template <typename T>
void printArray(const T *array, int count) {
  for (int i = 0; i < count && array[i] != '\0'; i++)
    cout << array[i] << " ";
  cout << endl;
}

void printArray(const char *array[], int count) {
  for (int i = 0; i < count; i++) {
    cout << setw(10) << array[i];
    if (i % 4 == 3) cout << endl;
  }
}

//StudybarCommentBegin
int main() {
  const int aCount = 5;
  const int bCount = 7;
  const int cCount = 6;
  const int sCount = 8;

  int a[aCount] = {1, 2, 3, 4, 5};
  double b[bCount] = {1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7};
  char c[cCount] = "HELLO";
  const char *strings[sCount] = {"one",  "two", "three", "four",
                                 "five", "six", "seven", "eight"};

  cout << "Array a contains:\n";
  printArray(a, aCount);

  cout << "\nArray b contains:\n";
  printArray(b, bCount);

  cout << "\nArray c contains:\n";
  printArray(c, cCount);

  cout << "\nArray strings contains:\n";
  printArray(strings, sCount);

  return 0;
}
//StudybarCommentEnd
