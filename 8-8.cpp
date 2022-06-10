#include <iostream>
#include <map>

using namespace std;

int diff(int a, int b) {
  return a >= b ? a - b : b - a;
}

int main() {
  map<int, int> m;
  m.insert(pair<int, int>(1000000000, 1));

  int num;
  cin >> num;
  int id, power;
  int closest1 = 1000000000, closest2 = 1000000000;
  for (; num > 0; num--) {
    cin >> id >> power;
    for (map<int, int>::const_iterator p = m.begin(); p != m.end(); p++)
      if (diff(p->first, power) <= diff(closest1, power)) {
        closest2 = closest1; closest1 = p->first;
      } else if (diff(p->first, power) <= diff(closest2, power)) {
        closest2 = p->first;
      }
    if (closest1 + closest2 == 2 * power)
      cout << id << ' ' << m[min(closest1, closest2)] << endl;
    else
      cout << id << ' ' << m[closest1] << endl;
    m.insert(pair<int, int>(power, id));
  }

  return 0;
}
