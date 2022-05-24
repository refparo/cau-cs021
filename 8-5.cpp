#include <iostream>
#include <stack>

using namespace std;

int main() {
  int num;
  cin >> num;

  stack<bool> st;
  while (num > 0) {
    st.push(num & 1);
    num >>= 1;
  }
  while (!st.empty()) {
    cout << st.top();
    st.pop();
  }
  return 0;
}
