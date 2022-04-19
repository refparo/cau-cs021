//StudybarCommentBegin
#include <iostream>

using namespace std;

class Animal {
public:
  virtual void bark() const { cout << "Animal::bark()" << endl; }
};
//StudybarCommentEnd

class Cat : public Animal {
public:
  void bark() const { cout << "miaomiao" << endl; }
};
class Dog : public Animal {
public:
  virtual void bark() const { cout << "wangwang" << endl; }
};
class Duck : public Animal {
public:
  void bark() { cout << " gaga" << endl; }
};

void AnimalBark_Ref(Animal &animal) { animal.bark(); }
void AnimalBark_Pointer(Animal *animal) { animal->bark(); }
void AnimalBark_var(Animal animal) { animal.bark(); }

int main() {
  Cat c;
  Dog d;
  Duck du;
  cout << "This sizeof(Animal):" << sizeof(Animal) << endl;
  cout << "This sizeof(c):" << sizeof(c) << endl;
  cout << "This sizeof(d):" << sizeof(d) << endl;
  cout << "This sizeof(du):" << sizeof(du) << endl;
  cout << "This sizeof(int *):" << sizeof(int *) << endl;
  cout << "--by Reference:" << endl;
  AnimalBark_Ref(c);
  AnimalBark_Ref(d);
  AnimalBark_Ref(du);
  cout << "--by Pointer:" << endl;
  AnimalBark_Pointer(&c);
  AnimalBark_Pointer(&d);
  AnimalBark_Pointer(&du);
  cout << "--by Variable:" << endl;
  AnimalBark_var(c);
  AnimalBark_var(d);
  AnimalBark_var(du);
  return 0;
}
