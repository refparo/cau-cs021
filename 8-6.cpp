#include <cstring>
#include <iostream>
#include <list>
#include <map>

using namespace std;

int main() {
  int n;
  cin >> n;

  char cmd[7];
  int op1, op2;
  map<int, list<int>> map;
  for (int i = 0; i < n; i++) {
    cin >> cmd;
    if (strcmp(cmd, "new") == 0) {
      cin >> op1;
      map.emplace(op1, list<int>());
    }
    if (strcmp(cmd, "add") == 0) {
      cin >> op1 >> op2;
      map[op1].merge(list<int>{op2});
    }
    if (strcmp(cmd, "merge") == 0) {
      cin >> op1 >> op2;
      map[op1].merge(map[op2]);
    }
    if (strcmp(cmd, "unique") == 0) {
      cin >> op1;
      map[op1].unique();
    }
    if (strcmp(cmd, "out") == 0) {
      cin >> op1;
      for (list<int>::iterator p = map[op1].begin(); p != map[op1].end(); p++)
        cout << *p << ' ';
      cout << endl;
    }
  }
  return 0;
}
