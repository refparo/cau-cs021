#include <cstdlib>
#include <iostream>

using namespace std;

template<typename T>
class Queue {
  T* array;
  int head;
  int count; // elem count
  int size; // capacity
public:
  Queue() : array(new T[0]), head(-1), count(0), size(0) {}
  ~Queue() { delete[] array; }

  inline const T& operator[](int idx) const {
    // assert 0 <= idx < size
    idx += head;
    return array[idx >= size ? idx - size : idx];
  }
  inline T& operator[](int idx) {
    // assert 0 <= idx < size
    idx += head;
    return array[idx >= size ? idx - size : idx];
  }

  void resize(int newSize) {
    if (newSize <= size) return;
    T* newArray = new T[newSize];
    for (int i = 0; i < count; i++)
      newArray[i] = (*this)[i];
    delete[] array;
    array = newArray;
    head = 0;
    size = newSize;
  }

  void insert(const T &item) {
    if (size == 0) resize(1);
    else if (count == size) resize(size * 2);
    (*this)[count] = item;
    count++;
  }
  T remove() {
    if (count == 0) {
      cout << "The queue is empty" << endl;
      exit(1);
    }
    int tmp = head;
    head++;
    if (head == size) head = 0;
    count--;
    return array[tmp];
  }

  const T& getFront() const {
    if (count == 0) {
      cout << "The queue is empty" << endl;
      exit(1);
    }
    return (*this)[0];
  }

  int getLength() const { return count; }

  bool isEmpty() const { return count == 0; }
  bool isFull() const { return count == size; }

  void clear() {
    delete[] array;
    array = new T[0];
    head = -1;
    count = 0;
    size = 0;
  }

  friend ostream& operator<<(ostream& out, const Queue &self) {
    if (self.count > 0) out << self[0];
    for (int i = 1; i < self.count; i++) out << ' ' << self[i];
    return out << endl;
  }
};

//StudybarCommentBegin
int main() {
  Queue<int> z1;
  int num[5] = {2, 4, 6, 8};
  int i, x;
  cin >> x;
  for (i = 0; i < 4; i++) {
    z1.insert(num[i]);
  }
  z1.insert(x);
  cout << z1;
  return 0;
}
//StudybarCommentEnd
