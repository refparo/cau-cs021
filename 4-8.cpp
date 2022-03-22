#include <cmath>
#include <iomanip>
#include <iostream>

#define EPSILON (1e-7)

using namespace std;

class Cmycomplex {
  double real, imag;

public:
  Cmycomplex(double x = 0, double y = 0) : real(x), imag(y) {}

  Cmycomplex operator-(const Cmycomplex &rhs) const {
    return Cmycomplex(real - rhs.real, imag - rhs.imag);
  }
  bool operator<(const Cmycomplex &rhs) const {
    return abs(*this) < abs(rhs);
  }
  bool operator==(const Cmycomplex &rhs) const {
    return abs(*this - rhs) < EPSILON;
  }

  friend double abs(const Cmycomplex &num) {
    double res = sqrt(num.real * num.real + num.imag * num.imag);
    return res;
  }

  friend ostream& operator<<(ostream &out, const Cmycomplex &num) {
    return out << '('
      << noshowpos << num.real
      << showpos << num.imag
      << "i)";
  }
  friend istream& operator>>(istream &in, Cmycomplex &num) {
    return in >> num.real >> num.imag;
  }
};

template<class T>
class Cassemblage {
  T arr[1000];
  int len;

  void push(T elem) {
    arr[len] = elem;
    len++;
  }
public:
  Cassemblage() : len(0) {}
  void Set(T *arr, int len) {
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
    T temp;
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
    cout << endl;
  }
};

int main() {
  Cassemblage<Cmycomplex> z1, z2, x1;
  Cmycomplex a1[1000], a2[1000];
  int i, n1, n2;
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
  x1 = z1 & z2;
  x1.Show();
  x1 = z1 - z2;
  x1.Show();
  return 0;
}
