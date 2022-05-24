#include <cstring>
#include <iostream>
#include <set>

using namespace std;

int main() {
  int n;
  cin >> n;

  char cmd[4];
  int operand;
  set<int> record;
  multiset<int> set;
  for (int i = 0; i < n; i++) {
    cin >> cmd >> operand;
    if (strcmp(cmd, "add") == 0) {
      record.insert(operand);
      set.insert(operand);
      cout << set.count(operand) << endl;
    }
    if (strcmp(cmd, "del") == 0) {
      cout << set.count(operand) << endl;
      set.erase(operand);
    }
    if (strcmp(cmd, "ask") == 0) {
      cout << record.count(operand) << ' ' << set.count(operand) << endl;
    }
  }
  return 0;
}
