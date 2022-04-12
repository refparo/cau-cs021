#include <iostream>
#include <vector>

using namespace std;

class List {
  int data;
  List *link;
public:
  List();
  List(const List &src);
  List(const vector<int> &src);

  void append(int val);
  /** insert after `pos` */
  void insertElement(int pos, int val);
  /** delete all occurrences of `val` */
  void deleteElement(int val);

  /** non-copying concat */
  void connect(const List &rhs);

  /** compares all the data stored in the list */
  bool isEqual(const List &rhs) const;
  void getLength() const;
  void travalList() const;
};

List::List() : data(0), link(NULL) {}
List::List(const List &src) : data(0), link(NULL) {
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
List::List(const vector<int> &src) : data(0), link(NULL) {
  List *last = this;
  // VC6 doesn't support iterators
  for (int i = 0; i < src.size(); i++) {
    List *tmp = new List();
    tmp->data = src[i];
    last->link = tmp;
    last = tmp;
  }
}

void List::append(int val) {
  List *last = this;
  while (last->link != NULL) last = last->link;
  last->link = new List();
  last->link->data = val;
}

void List::insertElement(int pos, int val) {
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

void List::deleteElement(int val) {
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

void List::connect(const List &rhs) {
  List *last = this;
  while (last->link != NULL) last = last->link;
  last->link = rhs.link;
  // shit
  cout << "After connect:" << endl;
}

bool List::isEqual(const List &rhs) const {
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

void List::getLength() const {
  int len = 0;
  for (const List *node = link; node != NULL; node = node->link)
    len++;
  cout << "The length of this List is " << len << "." << endl;
}

void List::travalList() const {
  for (const List *node = link; node != NULL; node = node->link)
    cout << "->" << node->data;
  cout << endl;
}

//StudybarCommentBegin
int main(void) {
  List list;
  list.append(10);
  list.append(8);
  list.append(12);
  list.append(100);
  list.append(8);
  list.travalList();

  list.insertElement(1, 20);
  list.travalList();

  list.deleteElement(2);
  list.deleteElement(10);
  list.travalList();

  list.deleteElement(8);
  list.travalList();
}
//StudybarCommentEnd
