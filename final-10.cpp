 	//StudybarCommentBegin
#include <iostream>
#include <list>
#include <string>

using namespace std;

class Observer { //抽象类
public:
  virtual void update(string message) = 0; //更新行为,纯虚函数
};

class WeixinUser : public Observer {
  string name; // 微信用户名
public:
  WeixinUser(string name) { this->name = name; }
  virtual void update(string message) {
    cout << endl << (name + " knows " + message);
    this->doSomething();
  }
  virtual void doSomething() { cout << endl << name << " is very happy"; }
};

class ReporterUser : public Observer {
  string name; // 微信用户名
public:
  ReporterUser(string name) { this->name = name; }

  virtual void update(string message) {
    cout << endl << (name + " knows " + message);
    this->doSomething();
  }
  void doSomething() { cout << endl << name << " is going to write a report"; }
};

class Subject { //抽象类
public:
  virtual void attach(Observer *observer) = 0; //增加订阅者,纯虚函数
  virtual void detach(Observer *observe) = 0;  //删除订阅者,纯虚函数
  virtual void notify(string message) = 0; //通知订阅者更新消息,纯虚函数
};

class SubscriptionSubject : public Subject {
  list<Observer *> weixinUserlist; //储存订阅公众号的用户
public:
  virtual void attach(Observer *observer);
  virtual void detach(Observer *observer);
  virtual void notify(string message);
};
//StudybarCommentEnd

void SubscriptionSubject::attach(Observer *observer) {
  weixinUserlist.push_back(observer);
}
void SubscriptionSubject::detach(Observer *observer) {
  weixinUserlist.remove(observer);
}
void SubscriptionSubject::notify(string message) {
  for (
    list<Observer*>::iterator p = weixinUserlist.begin();
    p != weixinUserlist.end();
    p++
  ) {
    (*p)->update(message);
  }
}

//StudybarCommentBegin
int main() {
  SubscriptionSubject CAUBlog;
  string name1, name2, name3;
  cin >> name1 >> name2 >> name3;

  WeixinUser zhangsan(name1), lisi(name2);
  ReporterUser wangwu(name3);
  //用户关注
  CAUBlog.attach(&zhangsan);
  CAUBlog.attach(&lisi);
  CAUBlog.attach(&wangwu);

  CAUBlog.notify("2018农大招生了");
  //用户取消关注
  CAUBlog.detach(&lisi);

  CAUBlog.notify("2018农大招生结束了");

  return 0;
}
//StudybarCommentEnd
