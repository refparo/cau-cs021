//StudybarCommentBegin
#include <iomanip>
#include <iostream>

using namespace std;

class shuzu {
  int size;
  double *ptr;

public:
  void getlength(int a);
  shuzu operator+(const shuzu &z);
  shuzu operator-(const shuzu &z);
  shuzu operator*(const shuzu &z);
  shuzu operator/(const shuzu &z);
  shuzu operator++(int);
  friend istream &operator>>(istream &in, shuzu &z);
  friend ostream &operator<<(ostream &out, const shuzu &z);
};
//StudybarCommentEnd

void shuzu::getlength(int a) {
  ptr = new double[a];
  size = a;
}

shuzu shuzu::operator+(const shuzu &z) {
  shuzu res;
  res.getlength(size);
  for (int i = 0; i < size; i++)
    res.ptr[i] = ptr[i] + z.ptr[i];
  return res;
}
shuzu shuzu::operator-(const shuzu &z) {
  shuzu res;
  res.getlength(size);
  for (int i = 0; i < size; i++)
    res.ptr[i] = ptr[i] - z.ptr[i];
  return res;
}
shuzu shuzu::operator*(const shuzu &z) {
  shuzu res;
  res.getlength(size);
  for (int i = 0; i < size; i++)
    res.ptr[i] = ptr[i] * z.ptr[i];
  return res;
}
shuzu shuzu::operator/(const shuzu &z) {
  shuzu res;
  res.getlength(size);
  for (int i = 0; i < size; i++)
    res.ptr[i] = ptr[i] / z.ptr[i];
  return res;
}

shuzu shuzu::operator++(int) {
  shuzu original;
  original.getlength(size);
  for (int i = 0; i < size; i++) {
    original.ptr[i] = ptr[i];
    ptr[i]++;
  }
  return original;
}

istream &operator>>(istream &in, shuzu &z) {
  for (int i = 0; i < z.size; i++)
    in >> z.ptr[i];
  return in;
}

ostream &operator<<(ostream &out, const shuzu &z) {
  out << fixed << setprecision(2);
  for (int i = 0; i < z.size; i++)
    out << z.ptr[i] << ' ';
  return out;
}

//StudybarCommentBegin
int main() {
  shuzu r1, r2, r4;
  int n;
  cin >> n;
  r1.getlength(n);
  r2.getlength(n);
  r4.getlength(n);
  cin >> r1 >> r2;
  cout << (r1 + r2) << endl;
  cout << (r1 - r2) << endl;
  cout << (r1 * r2) << endl;
  cout << (r1 / r2) << endl;
  r4 = r1++;
  cout << r4 << endl;
  cout << r1 << endl;
  return 0;
}
//StudybarCommentEnd
