#include <iomanip>
#include <iostream>
#include <vector>

using namespace std;

int main() {
  int n;
  cin >> n;

  vector<int> primes;
  for (int i = 2; i < n; i++) {
    for (vector<int>::iterator p = primes.begin(); p < primes.end(); p++)
      if (i % *p == 0) goto cont;
    primes.push_back(i);
    cont:;
  }
  for (vector<int>::iterator p = primes.begin(); p < primes.end(); p++) {
    cout << setw(5) << *p;
    if ((p - primes.begin() + 1) % 10 == 0) cout << endl;
  }
  return 0;
}
