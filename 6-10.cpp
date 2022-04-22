#include <cmath>
#include <iostream>

using namespace std;

template<typename T>
inline T min(T a, T b) {
  return a > b ? b : a;
}

template<typename T>
class DynamicVector {
  T *array;
  unsigned int mallocSize;
  unsigned int filledSize;
  int offset;

public:
  DynamicVector(int offset)
    : array(NULL), mallocSize(0), filledSize(0), offset(offset) {}
  DynamicVector(const DynamicVector &src)
    : array(NULL), mallocSize(0), filledSize(0), offset(src.offset) {
    resize(src.mallocSize);
    for (int i = 0; i < src.filledSize; i++) push_back(src.array[i]);
  }

  ~DynamicVector() {
    delete[] array;
  }

  unsigned int length() const { return filledSize; }
  unsigned int capacity() const { return mallocSize; }
  int firstIndex() const { return offset; }

  T& operator[](int i) {
    int realI = i - offset;
    if (realI < 0 || realI >= filledSize) {
      cout << endl << "Out Of Range";
      exit(1);
    }
    return array[realI];
  }
  const T& operator[](int i) const {
    int realI = i - offset;
    if (realI < 0 || realI >= filledSize) {
      cout << endl << "Out Of Range";
      exit(1);
    }
    return array[realI];
  }

  void push_back(const T& value) {
    if (filledSize >= mallocSize) resize(2 * mallocSize + 1);
    array[filledSize] = value;
    filledSize++;
  }

  int resize(unsigned int size) {
    if (size == mallocSize) return 0;
    filledSize = ::min(size, filledSize);
    T* newArray = new T[size];
    for (unsigned int i = 0; i < filledSize; i++)
      newArray[i] = array[i];
    delete[] array;
    mallocSize = size;
    array = newArray;
    if (size > mallocSize) return 1; else return -1;
  }
};

//StudybarCommentBegin
int main() {
  DynamicVector<int> ra(-2);
  int i, n;
  cin >> n;
  ra.push_back(-3);
  ra.push_back(-2);
  ra.push_back(-1);
  for (i = 0; i < n; i++) {
    ra.push_back(i);
  }
  cout << "\n malloSize is " << ra.capacity();
  cout << "\n numofItems is " << ra.length();
  cout << "\n StartIndex is " << ra.firstIndex() << endl;
  for (i = -2; i < n + 1; i++) {
    cout << ra[i] << " ";
  }
  cout << endl;
  DynamicVector<int> raCopy(ra);
  cout << "\n malloSize is " << raCopy.capacity();
  cout << "\n numofItems is " << raCopy.length();
  cout << "\n StartIndex is " << raCopy.firstIndex() << endl;
  cout << endl;
  for (i = -2; i < n + 1; i++) {
    cout << ++ra[i] << " ";
  }
  cout << endl;
  for (i = -2; i < n + 1; i++) {
    cout << raCopy[i] << " ";
  }

  return 0;
}
//StudybarCommentEnd

