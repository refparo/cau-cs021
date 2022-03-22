#include <iostream>

using namespace std;

class Cassemblage {
  int arr[1000];
  int len;

  void push(int elem) {
    arr[len] = elem;
    len++;
  }
public:
  Cassemblage() : len(0) {}
  void Set(int *arr, int len) {
    for (int i = 0; i < len; i++)
      this->arr[i] = arr[i];
    this->len = len;
    dedup();
  }
  void dedup() {
    sort();
    int offset = 0;
    int i;
    for (i = 0; i + offset + 1 < len; i++) {
      if (arr[i + offset] == arr[i + offset + 1]) offset++;
      if (offset > 0) arr[i] = arr[i + offset];
    }
    if (offset > 0) arr[i] = arr[i + offset];
    len -= offset;
  }
  void sort() {
    int temp;
    for (int i = len - 1; i > 0; i--)
      for (int j = 0; j < i; j++)
        if (arr[j + 1] < arr[j]) {
          temp = arr[j + 1];
          arr[j + 1] = arr[j];
          arr[j] = temp;
        }
  }

  Cassemblage operator+(const Cassemblage &rhs) const& {
    Cassemblage res;
    int i = 0, j = 0;
    while (i < len && j < rhs.len)
      if (arr[i] < rhs.arr[j]) {
        res.push(arr[i]);
        i++;
      } else if (arr[i] == rhs.arr[j]) {
        res.push(arr[i]);
        i++; j++;
      } else {
        res.push(rhs.arr[j]);
        j++;
      }
    for (; i < len; i++) res.push(arr[i]);
    for (; j < rhs.len; j++) res.push(rhs.arr[j]);
    return res;
  }
  Cassemblage operator&(const Cassemblage &rhs) const& {
    Cassemblage res;
    int i = 0, j = 0;
    while (i < len && j < rhs.len)
      if (arr[i] < rhs.arr[j]) {
        i++;
      } else if (arr[i] == rhs.arr[j]) {
        res.push(arr[i]);
        i++; j++;
      } else {
        j++;
      }
    return res;
  }
  Cassemblage operator-(const Cassemblage &rhs) const& {
    Cassemblage res;
    int i = 0, j = 0;
    while (i < len && j < rhs.len)
      if (arr[i] < rhs.arr[j]) {
        res.push(arr[i]);
        i++;
      } else if (arr[i] == rhs.arr[j]) {
        i++; j++;
      } else {
        j++;
      }
    for (; i < len; i++) res.push(arr[i]);
    return res;
  }

  void Show() {
    if (len == 0) cout << "empty";
    else for (int i = 0; i < len; i++)
      cout << arr[i] << " ";
  }
};

//StudybarCommentBegin
int main() {
  Cassemblage z1, z2, x1, x2, x3;
  int i, n1, n2, a1[1000], a2[1000];

  cin >> n1;
  for (i = 0; i < n1; i++) {
    cin >> a1[i];
  }
  z1.Set(a1, n1);

  cin >> n2;
  for (i = 0; i < n2; i++) {
    cin >> a2[i];
  }
  z2.Set(a2, n2);

  x1 = z1 + z2;
  x1.Show();
  cout << endl;

  x2 = z1 & z2;
  x2.Show();
  cout << endl;

  x3 = z1 - z2;
  x3.Show();

  return 0;
}
//StudybarCommentEnd
