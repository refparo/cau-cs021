#include <algorithm>
#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::vector;

int main() {
  vector<int> arr;
  int tmp;
  while ((void(cin >> tmp), !cin.fail()))
    arr.push_back(tmp);
  sort(arr.begin(), arr.end());
  for (size_t i = arr.size(); i != 0; i--)
    if (arr[i] % 2 == 1) cout << arr[i] << ' ';
  cout << arr[0] << ' ';
  for (size_t i = 1; i < arr.size(); i++)
    if (arr[i] % 2 == 0) cout << arr[i] << ' ';
  cout << endl;
  return 0;
}
