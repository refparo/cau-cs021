#include <iomanip>
#include <iostream>

using namespace std;

template<typename T>
void bubbleSort(T arr[], int len) {
  T tmp;
  for (int i = len - 1; i >= 0; i--)
    for (int j = 0; j < i; j++)
      if (arr[j] > arr[j + 1]) {
        tmp = arr[j];
        arr[j] = arr[j + 1];
        arr[j + 1] = tmp;
      }
}

//StudybarCommentBegin
int main() {
  const int arraySize = 10;
  int a[arraySize] = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1}, i;

  cout << "Integer data items in original order\n";

  for (i = 0; i < arraySize; ++i)
    cout << setw(6) << a[i];

  bubbleSort(a, arraySize);

  cout << "\nInteger data items in ascending order\n";

  for (i = 0; i < arraySize; ++i)
    cout << setw(6) << a[i];

  cout << "\n\n";

  double b[arraySize] = {10.1, 9.9, 8.8, 7.7, 6.6, 5.5, 4.4, 3.3, 2.2, 1.1};

  cout << "double point data items in original order\n";

  for (i = 0; i < arraySize; ++i)
    cout << setw(6) << b[i];

  bubbleSort(b, arraySize);

  cout << "\ndouble point data items in ascending order\n";

  for (i = 0; i < arraySize; ++i)
    cout << setw(6) << b[i];

  cout << endl;

  return 0;

}
//StudybarCommentEnd
