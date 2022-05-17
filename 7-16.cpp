//StudybarCommentBegin
#include <iostream>
using namespace std;

class IElectricalEquipment {
public:
  virtual void PowerOn() = 0;
  virtual void PowerOff() = 0;
  virtual ~IElectricalEquipment() {
    cout << "\nThis is Virtual ~IElectricalEquipment()";
  }
};

class Switch {
public:
  IElectricalEquipment *Elec;
  virtual void On() = 0;
  virtual void Off() = 0;
  virtual ~Switch() { cout << "\nThis is Virtual ~Switch()"; }
};
//StudybarCommentEnd

class Fan : public IElectricalEquipment {
  void PowerOn() { cout << "风扇打开" << endl; }
  void PowerOff() { cout << "风扇关闭" << endl; }
};

class Light : public IElectricalEquipment {
  void PowerOn() { cout << "电灯打开" << endl; }
  void PowerOff() { cout << "电灯关闭" << endl; }
};

class NormalSwitch : public Switch {
  void On() {
    cout << "Normal Switch On" << endl;
    Elec->PowerOn();
  }
  void Off() {
    cout << "Normal Switch Off" << endl;
    Elec->PowerOff();
  }
};

class FancySwitch : public Switch {
  void On() {
    cout << "Fancy Switch On" << endl;
    Elec->PowerOn();
  }
  void Off() {
    cout << "Fancy Switch Off" << endl;
    Elec->PowerOff();
  }
};

//StudybarCommentBegin
int main() {
  IElectricalEquipment* fan = new Fan();
  IElectricalEquipment* light = new Light();

  Switch* fancySwitch = new FancySwitch();
  Switch* normalSwitch = new NormalSwitch();

  fancySwitch->Elec = fan;

  fancySwitch->On();
  fancySwitch->Off();

  normalSwitch->Elec = light;
  normalSwitch->On();
  normalSwitch->Off();

  fancySwitch->Elec = light;
  fancySwitch->On();
  fancySwitch->Off();

  delete fan;
  delete light;
  delete fancySwitch;
  delete normalSwitch;

  return 0;
}
//StudybarCommentEnd
