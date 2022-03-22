#include <iomanip>
#include <iostream>

using namespace std;

template<class T, int n>
class Array {
  T ptr[n];
  static int arrayCount;
public:
  Array(): ptr{} { arrayCount++; }
  int getSize() const { return n; }
  friend ostream& operator<<(ostream& out, const Array<T, n> &self) {
    for (int i = 0; i < n; i++) out << self.ptr[i] << ' ';
    return out << endl;
  }
  friend istream& operator>>(istream& in, Array<T, n> &self) {
    for (int i = 0; i < n; i++) in >> self.ptr[i];
    return in;
  }
  static int getArrayCount() { return arrayCount; }
};

template<class T, int n>
int Array<T, n>::arrayCount = 0;

//StudybarCommentBegin
int main() {
  Array<int, 5> intArray1;

  cin >> intArray1;

  Array<int, 5> intArray2;

  cin >> intArray2;

  Array<float, 5> floatArray;

  cin >> floatArray;

  cout << "\nIntArray1 contains " << intArray1.getSize() << " Elements.\n";
  cout << "The values in intArray are:\n";
  cout << intArray1;

  cout << "\nIntArray2 contains " << intArray2.getSize() << " Elements.\n";
  cout << "The values in intArray are:\n";
  cout << intArray2;

  cout << "\nDoubleArray contains " << floatArray.getSize() << " Elements.\n";
  cout << "The values in the doubleArray are:\n";
  cout << floatArray;

  cout << "\nThere are " << Array<int, 5>::getArrayCount()
    << " Array<int,5> objects.\n";
  cout << "\nThere are " << Array<float, 5>::getArrayCount()
    << " Array<float,5> objects.\n";

  return 0;
}
//StudybarCommentEnd
