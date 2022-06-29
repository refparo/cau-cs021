#include <iostream>
#include <set>
#include <string>

using std::size_t;
using std::cin;
using std::cout;
using std::set;
using std::getline;
using std::string;

size_t ord(char c) {
  return size_t(c >= 'a' ? c - ('a' - 26) : c - 'A');
}
char chr(size_t i) {
  return char(i >= 26 ? 'a' - 26 + i : 'A' + i);
}

typedef set<char>::iterator iter;

int main() {
  size_t relevance[52][52] = {{0}};

  string line;
  std::set<char> receipt;
  while (line != "00000") {
    getline(cin, line);
    receipt.insert(line.begin(), line.end());
    for (iter p = receipt.begin(); p != receipt.end(); p++) {
      iter q = p;
      q++;
      for (; q != receipt.end(); q++)
        relevance[ord(*p)][ord(*q)]++;
    }
    receipt.clear();
  }

  size_t max = 0;
  for (size_t i = 1; i < 52 * 52; i++)
    if (*(*relevance + i) > *(*relevance + max)) max = i;
  cout << chr(max / 52) << chr(max % 52);

  return 0;
}
