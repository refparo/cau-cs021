//StudybarCommentBegin
#include <iostream>
#include <string>

using namespace std;

class Person {
  int age;
public:
  virtual int getage() { return age; }
  void setage(int age) { this->age = age; }
};

class Student : public Person {
  int id;
  int score;
  virtual int getid() { return id; }
  virtual int getscore() { return score; }
public:
  void set(int age, int id, int score) {
    setage(age);
    this->id = id;
    this->score = score;
  }
};
//StudybarCommentEnd

typedef int (*Fun)(void);

#define peek(obj, j) (*(Fun **)(&obj))[j]

// can't get this UB right
int main() {
  int x, y, z;
  int n;
  cin >> n;
  Student* arr = new Student[n];
  for (int i = 0; i < n; i++) {
   cin >> x >> y >> z;
   arr[i].set(x, y, z);
  }
  int max = 0;
  int maxSco = peek(arr[max], 2)();
  for (int j = 1; j < n; j++)
    if ((z = peek(arr[j], 2)()) > maxSco) {
      max = j;
      maxSco = z;
    }
  x = peek(arr[max], 0)();
  y = peek(arr[max], 1)();
  cout << x << ' ' << y << ' ' << maxSco << endl;
  delete[] arr;
  return 0;
}
