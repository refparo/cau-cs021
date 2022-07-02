#include <iostream>

using namespace std;

class CPU {
public:
  virtual void work() = 0;
};
class VideoCard {
public:
  virtual void work() = 0;
};
class Memory {
public:
  virtual void work() = 0;
};

class InterCPU : public CPU {
public:
  virtual void work() {
    cout << "Inter的CPU开始计算了！" << endl;
  }
};
class InterVideoCard : public VideoCard {
public:
  virtual void work() {
    cout << "Inter的显卡开始显示了！" << endl;
  }
};
class InterMemory : public Memory {
public:
  virtual void work() {
    cout << "Inter的内存条开始存储了！" << endl;
  }
};

class LenovoCPU : public CPU {
public:
  virtual void work() {
    cout << "Lenovo的CPU开始计算了！" << endl;
  }
};
class LenovoVideoCard : public VideoCard {
public:
  virtual void work() {
    cout << "Lenovo的显卡开始显示了！" << endl;
  }
};
class LenovoMemory : public Memory {
public:
  virtual void work() {
    cout << "Lenovo的内存条开始存储了！" << endl;
  }
};

class Computer {
  CPU* cpu;
  VideoCard* gpu;
  Memory* mem;
public:
  Computer(CPU* cpu, VideoCard* gpu, Memory* mem)
    : cpu(cpu), gpu(gpu), mem(mem) {}
  void work() {
    cpu->work();
    gpu->work();
    mem->work();
  }
};

//StudybarCommentBegin
int main() {
  CPU *intercpu = new InterCPU;
  VideoCard *intercard = new InterVideoCard;
  Memory *intermemory = new InterMemory;
  //创建第一台电脑
  cout << "第一台电脑开始工作:" << endl;
  Computer *computer1 = new Computer(intercpu, intercard, intermemory);
  computer1->work();
  delete computer1;

  cout << "-----------------" << endl;
  cout << "第二台电脑开始工作:" << endl;
  //第二台电脑组装
  Computer *computer2 =
      new Computer(new LenovoCPU, new LenovoVideoCard, new LenovoMemory);
  computer2->work();
  delete computer2;

  cout << "-----------------" << endl;
  cout << "第三台电脑开始工作:" << endl;
  //第三台电脑组装
  Computer *computer3 =
      new Computer(new LenovoCPU, new InterVideoCard, new LenovoMemory);
  computer3->work();
  delete computer3;
}
//StudybarCommentEnd
