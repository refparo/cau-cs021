//StudybarCommentBegin
#include <iostream>

using namespace std;
//StudybarCommentEnd

template<typename T>
T middle(T arr[3]) {
  int min = 0;
  for (int i = 1; i < 3; i++) if (arr[i] < arr[min]) min = i;
  int mid = min == 0 ? 1 : 0;
  for (int i = 0; i < 3; i++)
    if (i == min) continue;
    else if (arr[i] < arr[mid]) mid = i;
  return arr[mid];
}

//StudybarCommentBegin
int main() {
  int iNumber[3] = {45, 3, 89};
  double dNumber[3] = {12.4, 6, 55.8};
  unsigned uNumber[3] = {345, 776, 565};

  cout << "\nThe numbers are ";
  for (int i = 0; i < 3; i++)
    cout << iNumber[i] << "\t";
  cout << endl << "the middle of them is " << middle(iNumber) << endl;

  cout << "\nThe numbers are ";
  for (int i = 0; i < 3; i++)
    cout << dNumber[i] << "\t";
  cout << endl << "the middle of them is " << middle(dNumber) << endl;

  cout << "\nThe numbers are ";
  for (int i = 0; i < 3; i++)
    cout << uNumber[i] << "\t";
  cout << endl << "the middle of them is " << middle(uNumber) << endl;

  return 0;
}
//StudybarCommentEnd
