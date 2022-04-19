#include <iostream>

using namespace std;

class Animal {
protected:
  unsigned age;
public:
  Animal(unsigned age = 1) : age(age) {}
  int TellAge() const {
    cout << "The animal's age is " << age << endl;
    return age;
  }
  virtual void bark() const { cout << "Animal::bark()" << endl; }
};

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

class Bird : public Animal {
  unsigned wingNum;
public:
  Bird(unsigned age = 2, unsigned wingNum = 2) : wingNum(wingNum) {
    this->age = 2; // ???
  }
  int TellAge() const {
    cout << "I am a bird with " << wingNum
      << " Wings, my age is " << age << endl;
    return age;
  }
  void bark() const { cout << "jiji" << endl; }
};

void AnimalBark_Pointer(Animal *animal) {
  animal->bark();
  animal->Animal::TellAge();
}

//StudybarCommentBegin
int main() {
  Cat c;
  Dog d;
  Duck du;
  Bird *pbird = new Bird(3);

  cout << "This sizeof(Animal):" << sizeof(Animal) << endl;
  cout << "This sizeof(c):" << sizeof(c) << endl;
  cout << "This sizeof(d):" << sizeof(d) << endl;
  cout << "This sizeof(du):" << sizeof(du) << endl;
  cout << "This sizeof(Bird):" << sizeof(Bird) << endl;
  cout << "This sizeof(int *):" << sizeof(int *) << endl;

  cout << "--by Pointer:" << endl;
  AnimalBark_Pointer(&c);
  AnimalBark_Pointer(&d);
  AnimalBark_Pointer(&du);
  AnimalBark_Pointer(pbird);
  pbird->TellAge();

  return 0;
}
//StudybarCommentEnd

