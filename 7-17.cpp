//StudybarCommentBegin
#include <iostream>
#include <string>

using namespace std;

class GameCharacter {
public:
  GameCharacter(string name) : HealthValue(10), m_name(name) {}

  int BeHitted() {
    int v = this->ChangeHealthValue();
    if (v <= 0)
      cout << endl << GetName() << "is dead";
    return v;
  }
  int GetHealthValue() const { return this->HealthValue; }
  string GetName() const { return m_name; }

protected:
  virtual int ChangeHealthValue() = 0;
  int HealthValue;
  string m_name;
};
//StudybarCommentEnd

class Player : public GameCharacter {
public:
  Player(string name) : GameCharacter(name) {}
  int ChangeHealthValue() {
    return HealthValue -= 1;
  }
};

class Monster : public GameCharacter {
public:
  Monster(string name) : GameCharacter(name) {}
  int ChangeHealthValue() {
    return HealthValue -= 2;
  }
};

//StudybarCommentBegin
int main() {
  Player p("Player");
  Monster m("Monster");

  p.BeHitted();
  m.BeHitted();

  std::cout << p.GetName() << ": " << p.GetHealthValue() << std::endl;
  std::cout << m.GetName() << ": " << m.GetHealthValue() << std::endl;

  return 0;
}
//StudybarCommentEnd
