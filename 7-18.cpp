 	//StudybarCommentBegin
#include <iostream>

using namespace std;

typedef struct tagNode {
  int value;
  tagNode* pNext;
} Node;

class JTList {
public:
  JTList() : m_pHead(NULL), m_pTail(NULL) {}
  ~JTList();
  Node* First() const;
  Node* Last() const;
  void Append(const int &);

private:
  Node* m_pHead;
  Node* m_pTail;
  long m_lCount;
};

JTList::~JTList() {
  Node* pCurrent = m_pHead;
  Node* pNextNode = NULL;
  while (pCurrent) {
    pNextNode = pCurrent->pNext;
    delete pCurrent;
    pCurrent = pNextNode;
  }
}

void JTList::Append(const int &value) {
  Node* pInsertNode = new Node;
  pInsertNode->value = value;
  pInsertNode->pNext = NULL;
  // This list is empty
  if (m_pHead == NULL) {
    m_pHead = m_pTail = pInsertNode;
  } else {
    m_pTail->pNext = pInsertNode;
    m_pTail = pInsertNode;
  }
  ++m_lCount;
}
//StudybarCommentEnd

Node* JTList::First() const {
  return m_pHead;
}
Node* JTList::Last() const {
  return m_pTail;
}

class Iterator {
public:
  virtual void First() = 0;
  virtual bool IsDone() = 0;
  virtual void Next() = 0;
  virtual Node* CurrentItem() = 0;
};

class JTListIterator : public Iterator {
  Node* first;
  Node* curr;
public:
  JTListIterator(const JTList* list) : first(list->First()), curr(first) {}
  void First() { curr = first; }
  bool IsDone() { return curr == NULL; }
  void Next() { curr = curr->pNext; }
  Node* CurrentItem() { return curr; }
};

class ArrayIterator : public Iterator {
  Node* arr;
  int curr, len;
public:
  ArrayIterator(Node* arr, int len) : arr(arr), curr(0), len(len) {}
  void First() { curr = 0; }
  bool IsDone() { return curr >= len; }
  void Next() { curr++; }
  Node* CurrentItem() { return arr + curr; }
};

//StudybarCommentBegin
int findValue(Iterator* pIterator, int value) {
  int i = 0;
  for (pIterator->First(); !pIterator->IsDone(); pIterator->Next()) {
    if (pIterator->CurrentItem()->value == value) {
      return i;
    }
    i++;
  }
  return -1;
}

int main() {
  JTList* pJTList = new JTList;
  int i;
  for (i = 0; i < 20; i++) {
    pJTList->Append(i * 10);
  }
  Node temp[10] = {{0, NULL}, {9, NULL}, {8, NULL}, {7, NULL}, {6, NULL},
                   {5, NULL}, {4, NULL}, {3, NULL}, {2, NULL}, {1, NULL}};

  Iterator* pListIterator = new JTListIterator(pJTList);
  Iterator* pArrayIterator = new ArrayIterator(temp, 10);
  int x, y;
  cin >> x >> y;
  cout << "\nIn the list, findValue give the index: "
       << findValue(pListIterator, x);
  cout << "\nIn the Array, findValue give the index: "
       << findValue(pArrayIterator, y);

  delete pListIterator;
  delete pJTList;
  delete pArrayIterator;

  return 0;
}
//StudybarCommentEnd
