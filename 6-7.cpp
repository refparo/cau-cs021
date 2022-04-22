#include <iostream>

using namespace std;

template<typename T>
class DynamicArray {
  T *array;
  unsigned int mallocSize;

public:
  DynamicArray(unsigned int length, const T &content) : mallocSize(length) {
    cout << endl << "new T[" << this->mallocSize
      << "] malloc " << this->mallocSize << "*" << sizeof(T)
      << "=" << this->mallocSize * sizeof(T) << " bytes memory in heap";
    array = new T[length];
    for (unsigned int i = 0; i < length; i++)
      array[i] = content;
  }
  // deep copy
  DynamicArray(const DynamicArray& arr) : mallocSize(arr.mallocSize) {
    cout << endl << "Copy Constructor is called";
    array = new T[mallocSize];
    for (unsigned int i = 0; i < mallocSize; i++)
      array[i] = arr[i];
  }

  ~DynamicArray() {
    cout << endl
      << "delete[] array free " << this->mallocSize << "*" << sizeof(T)
      << "=" << this->mallocSize * sizeof(T) << " bytes memory in heap";
    delete[] array;
  }

  unsigned int capacity() const { return mallocSize; }

  T& operator[](unsigned int i) { return array[i]; }
  T& operator[](unsigned int i) const { return array[i]; }

  // deep copy assignment
  DynamicArray& operator=(const DynamicArray& rhs) {
    cout << endl << "operator = is called";
    delete[] array;
    mallocSize = rhs.mallocSize;
    array = new T[mallocSize];
    for (unsigned int i = 0; i < mallocSize; i++)
      array[i] = rhs[i];
    return *this;
  }

  int resize(unsigned int size, const T& fill) {
    cout << endl << "resize is called";
    if (size == mallocSize) return 0;
    else if (size < mallocSize) {
      T* newArray = new T[size];
      for (unsigned int i = 0; i < size; i++)
        newArray[i] = array[i];
      delete[] array;
      mallocSize = size;
      array = newArray;
      return -1;
    } else {
      T* newArray = new T[size];
      for (unsigned int i = 0; i < mallocSize; i++)
        newArray[i] = array[i];
      delete[] array;
      for (unsigned int i = mallocSize; i < size; i++)
        newArray[i] = fill;
      mallocSize = size;
      array = newArray;
      return 1;
    }
  }
};

class Point {
public:
  Point(int x = 0, int y = 0) : x(x), y(y) {
    cout << endl << "Point is called!";
  }

  ~Point() { cout << endl << "~Point is called!"; }

  friend ostream& operator<<(ostream& out, const Point& self) {
    return out << "(" << self.x << "," << self.y << ")";
  }

private:
  int x, y;
};

//StudybarCommentBegin
int main() {
  int length, i;
  cin >> length;

  DynamicArray<Point> iarray(length, Point(3));

  DynamicArray<Point> iarray2(iarray), iarray3(iarray2);

  cout << endl;
  for (i = 0; i < length; i++) {
    cout << iarray3[i] << " ";
    iarray[i] = Point(i, i + 1);
  }
  iarray3 = iarray2 = iarray;
  cout << endl;
  for (i = 0; i < length; i++) {
    cout << iarray3[i] << " ";
  }

  return 0;
}
//StudybarCommentEnd
