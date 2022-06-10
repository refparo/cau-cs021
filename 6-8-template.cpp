#include <cstdio>
#include <iostream>

using namespace std;

template<typename T>
class List {
  T data;
  List *link;
public:
  List();
  List(const List &src);
  List(const T src[], int len);

  void append(T val);
  /** insert after `pos` */
  void insertElement(int pos, T val);
  /** delete all occurrences of `val` */
  void deleteElement(T val);

  /** non-copying concat */
  void connect(const List &rhs);

  /** compares all the data stored in the list */
  bool isEqual(const List &rhs) const;
  int getLength() const;
  void travalList() const;
};

template<typename T>
List<T>::List() : data(0), link(NULL) {}
template<typename T>
List<T>::List(const List &src) : data(0), link(NULL) {
  const List *srcLast = &src;
  List *last = this;
  while (srcLast->link != NULL) {
    List *tmp = new List();
    tmp->data = srcLast->link->data;
    last->link = tmp;
    last = tmp;
    srcLast = srcLast->link;
  }
}
template<typename T>
List<T>::List(const T src[], int len) : data(0), link(NULL) {
  List *last = this;
  for (int i = 0; i < len; i++) {
    List *tmp = new List();
    tmp->data = src[i];
    last->link = tmp;
    last = tmp;
  }
}

template<typename T>
void List<T>::append(T val) {
  List *last = this;
  while (last->link != NULL) last = last->link;
  last->link = new List();
  last->link->data = val;
}

template<typename T>
void List<T>::insertElement(int pos, T val) {
  List *node = this;
  while (node->link != NULL)
    if (pos < 0) {
      List *tmp = new List();
      tmp->data = val;
      tmp->link = node->link;
      node->link = tmp;
      return;
    } else {
      node = node->link;
      pos--;
    }
  cout << "List index overflow!" << endl;
}

template<typename T>
void List<T>::deleteElement(T val) {
  List *node = this;
  bool flag = false;
  while (node->link != NULL)
    if (node->link->data == val) {
      List *tmp = node->link->link;
      delete node->link;
      node->link = tmp;
      flag = true;
    } else node = node->link;
  if (!flag) cout << "Element " << val << " not Found." << endl;
}

template<typename T>
void List<T>::connect(const List &rhs) {
  List *last = this;
  while (last->link != NULL) last = last->link;
  last->link = rhs.link;
}

template<typename T>
bool List<T>::isEqual(const List &rhs) const {
  const List *node = this;
  const List *rhsNode = &rhs;
  while (node->link != NULL && rhsNode->link != NULL) {
    if (node->link->data != rhsNode->link->data) return false;
    node = node->link;
    rhsNode = rhsNode->link;
  }
  if (node->link != NULL || rhsNode->link != NULL) return false;
  else return true;
}

template<typename T>
int List<T>::getLength() const {
  int len = 0;
  for (const List *node = link; node != NULL; node = node->link)
    len++;
  return len;
}

template<typename T>
void List<T>::travalList() const {
  for (const List *node = link; node != NULL; node = node->link)
    cout << "->" << node->data;
  cout << endl;
}

//StudybarCommentBegin
int main() {
  int a, i, lengthA, lengthB;
  int in1[100], in2[100];

  for (i = 0, lengthA = 1; cin >> a; i++, lengthA++) {
    in1[i] = a;
    if ('\n' == getchar()) {
      break;
    }
  }
  for (i = 0, lengthB = 1; cin >> a; i++, lengthB++) {
    in2[i] = a;
    if ('\n' == getchar()) {
      break;
    }
  }
  List<int> listA(in1, lengthA), listB(in2, lengthB);

  listA.travalList();
  listB.travalList();
  if (listA.isEqual(listB))
    cout << "They are the same LinkList." << endl;
  else
    cout << "They are different LinkList." << endl;
  listA.connect(listB);
  cout << "After connect:" << endl;
  cout << "The length of this List is " << listA.getLength() << "." << endl;
  listA.travalList();
}
//StudybarCommentEnd
