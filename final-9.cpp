//StudybarCommentBegin
#include <iostream>
//#include <windows.h>
using namespace std;

template<typename T>
inline void SAFE_DELETE(T *p) {
  if (p != NULL) {
    delete p;
    p = NULL;
  }
}

long InterlockedIncrement(volatile long* x) { return ++*x; }
long InterlockedDecrement(volatile long* x) { return --*x; }

// KRefCount是一个多线程安全的计数器对象，大家仅关注其外部接口（功能），不用关心内部实现。
class KRefCount {
public:
  KRefCount() : m_nCount(0) {}

  long AddRef() {
    return InterlockedIncrement(&m_nCount);
  } //给m_nCount加一，用InterlockedIncrement是多线程安全。
  long Release() {
    return InterlockedDecrement(&m_nCount);
  } //给m_nCount减一，用InterlockedIncrement是多线程安全。
  void Reset() { m_nCount = 0; }

private:
  // volatile 告诉编译器， m_nCount 这个变量不允许做寄存器优化。
  volatile long m_nCount;
};

template<typename T>
class SmartPtr {
private:
  KRefCount *m_pReference;
  T *m_pData;

public:
  SmartPtr(T *pValue);
  ~SmartPtr(void);
  inline T& operator*();
  inline T* operator->();

  SmartPtr<T> &operator=(const SmartPtr<T> &sp);
};
//StudybarCommentEnd

template<typename T>
SmartPtr<T>::SmartPtr(T *pValue)
  : m_pReference(new KRefCount), m_pData(pValue) {}

template<typename T>
SmartPtr<T>::~SmartPtr() {
  // why can't I access the ref count?
  if (*(long*)m_pReference == 0) {
    SAFE_DELETE(m_pReference);
    SAFE_DELETE(m_pData);
  } else m_pReference->Release();
}

template<typename T>
T& SmartPtr<T>::operator*() {
  return *m_pData;
}
template<typename T>
T* SmartPtr<T>::operator->() {
  return m_pData;
}

template<typename T>
SmartPtr<T>& SmartPtr<T>::operator=(const SmartPtr<T> &sp) {
  this->~SmartPtr();
  sp.m_pReference->AddRef();
  m_pReference = sp.m_pReference;
  m_pData = sp.m_pData;
  return *this;
}

//StudybarCommentBegin
class CTest {
public:
  CTest(int b) : a(b) { cout << "\n CTest(" << a << " ) is called"; }
  ~CTest() { cout << "\n ~CTest(" << a << ") is called"; }
  void ShowAddOne() { cout << "\n++a= " << ++a; }

private:
  int a;
};

int main() {
  int x;
  cin >> x;
  SmartPtr<CTest> pSmartPtr1(new CTest(x));
  SmartPtr<CTest> pSmartPtr2 = new CTest(20);
  CTest *p = new CTest(30);
  pSmartPtr1 = pSmartPtr2;
  pSmartPtr1->ShowAddOne();
  (*pSmartPtr2).ShowAddOne();
}
//StudybarCommentEnd
