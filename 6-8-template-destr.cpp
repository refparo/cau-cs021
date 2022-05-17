//StudybarCommentBegin
#include <iostream>

using namespace std;

template<typename T>
class List {
  T data;
  List *link;
public:
  List();
  ~List();
  void append(const T &val);
  void insertElement(int pos, const T &val);
  void deleteElement(const T &val);
  void travalList() const;
};

class Point {
  int x, y;
public:
  Point(int nx = 0, int ny = 0) {
    x = nx;
    y = ny;
    cout << "\nPoint(" << x << "," << y << ") is called!";
  }
  ~Point() {
    cout << "\n~Point(" << x << "," << y << ") is called!";
  }
  friend ostream& operator<<(ostream &out, const Point &p);
  bool operator==(const Point &p) {
    if (x != p.x || y != p.y)
      return false;
    return true;
  }
};
//StudybarCommentEnd

ostream& operator<<(ostream &out, const Point &p) {
  return out << '(' << p.x << ',' << p.y << ')';
}

template<typename T>
List<T>::List() : data(0), link(NULL) {}

template<typename T>
List<T>::~List() {
  // do not use recursive destruction
  // as there is an IMPLICIT requirement of destruction order
  // fuck.
  if (link == NULL) return;
  List* node = link;
  for (
    List* next = node->link;
    next != NULL;
    node = next, next = node->link
  ) {
    node->link = NULL;
    delete node;
  }
  delete node;
}

template<typename T>
void List<T>::append(const T &val) {
  List *last = this;
  while (last->link != NULL) last = last->link;
  last->link = new List();
  last->link->data = val;
}

template<typename T>
void List<T>::insertElement(int pos, const T &val) {
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
void List<T>::deleteElement(const T &val) {
  List *node = this;
  bool flag = false;
  while (node->link != NULL)
    if (node->link->data == val) {
      List *tmp = node->link->link;
      node->link->link = NULL;
      delete node->link;
      node->link = tmp;
      flag = true;
    } else node = node->link;
  if (!flag) cout << "\nElement " << val << " not Found.";
}

template<typename T>
void List<T>::travalList() const {
  cout << '\n'; // fuck
  for (const List *node = link; node != NULL; node = node->link)
    cout << "->" << node->data;
}

//StudybarCommentBegin
int main(void) {
  List<Point> list;
  list.append(Point(1, 2));
  list.append(Point(2, 3));
  list.append(Point(3, 4));
  list.append(Point(5, 6));
  list.append(Point(1, 2));
  list.travalList();

  list.insertElement(1, Point(7, 8));
  list.travalList();

  list.deleteElement(Point(1, 2));
  list.travalList();

  list.deleteElement(Point(7, 8));
  list.travalList();
  list.deleteElement(Point(9, 0));
}
//StudybarCommentEnd
