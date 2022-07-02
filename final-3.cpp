//StudybarCommentBegin
#include <iostream>
#include <vector>

using namespace std;

int main() {
  vector<int> arr;
  int i;
  int a;
  for (i = 0; i < 4; i++) {
    cin >> a;
    arr.push_back(a);
  }
  vector<int>::iterator it;
  it = arr.begin();
//StudybarCommentEnd
  while (it != arr.end())
    if (*it == 8) arr.erase(it);
    else it++;
//StudybarCommentBegin
  cout << "After remove 8:\n";
  for (it = arr.begin(); it < arr.end(); ++it)
    cout << *it << endl;
}
//StudybarCommentEnd
