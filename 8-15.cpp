#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>

using std::sort;
using std::istream;
using std::ostream;
using std::cin;
using std::cout;
using std::endl;
using std::vector;

int main() {
  vector<double> arr;
  double tmp;
  while ((void(cin >> tmp), tmp != 0)) {
    for (size_t i = 0; i < arr.size(); i++)
      if (arr[i] == tmp) {
        cout << "  " << tmp << " is duplicated" << endl;
        goto cont;
      }
    arr.push_back(tmp);
    cont:;
  }
  sort(arr.begin(), arr.end());
  cout << "  <= medium:";
  for (size_t i = 0; i < arr.size(); i++) {
    if (i == arr.size() / 2)
      cout << ' ' << arr[i] << endl << "  >= medium:";
    cout << ' ' << arr[i];
  }
  cout << endl;
  return 0;
}
