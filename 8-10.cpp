#include <algorithm>
#include <cmath>
#include <cstddef>
#include <ctime>
#include <iostream>
#include <vector>

using std::size_t;
using std::cin;
using std::cout;
using std::vector;

template<typename T>
class heap {
  vector<T> inner;
public:
  heap() {
    std::make_heap(inner.begin(), inner.end());
  }

  typedef typename vector<T>::reference reference;

  size_t size() const { return inner.size(); }

  void push(const T &elem) {
    inner.push_back(elem);
    std::push_heap(inner.begin(), inner.end());
  }
  reference front() {
    return inner.front();
  }
  void pop() {
    std::pop_heap(inner.begin(), inner.end());
    inner.pop_back();
  }
};

double rand(double min, double max) {
  return double(rand()) / RAND_MAX * (max - min) + min;
}

class Bacteria {
  double split_time;
public:
  Bacteria(double birth = 0) : split_time(birth + rand(500, 2000)) {}
  double get_split_time() const { return split_time; }
  void split(heap<Bacteria> &petri) {
    petri.push(Bacteria(split_time));
    petri.push(Bacteria(split_time));
  }
  bool operator<(const Bacteria &rhs) const {
    return split_time > rhs.split_time;
  }
};

int main() {
  double t;
  cin >> t;

  srand(unsigned(time(NULL)));

  const int ITERATION = 50000;
  size_t num = 0;

  for (int i = 0; i < ITERATION; i++) {
    heap<Bacteria> petri;
    Bacteria bac;
    while (bac.get_split_time() < t) {
      bac.split(petri);
      bac = petri.front();
      petri.pop();
    }
    num += petri.size() + 1;
  }

  cout << round(double(num) / ITERATION);
  return 0;
}
