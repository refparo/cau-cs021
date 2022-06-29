#include <algorithm>
#include <iostream>
#include <vector>

using std::sort;
using std::istream;
using std::cin;
using std::cout;
using std::endl;
using std::vector;

typedef char vol_list[5];

class Student {
  size_t id;
  short score;
  vol_list volunteer;
public:
  Student() {}
  size_t getID() const { return id; }
  vol_list& getVolunteer() { return volunteer; }
  bool end() const { return id == 0 && score == 0; }
  bool operator<(const Student &rhs) const {
    return score < rhs.score;
  }
  friend istream& operator>>(istream &in, Student &self) {
    in >> self.id >> self.score;
    for (int i = 0; i < 5; i++)
      in >> self.volunteer[i];
    return in;
  }
};

int main() {
  size_t schools[10];
  for (int i = 0; i < 10; i++)
    cin >> schools[i];

  vector<Student> students;
  Student stu;
  while ((void(cin >> stu), !stu.end()))
    students.push_back(stu);
  sort(students.begin(), students.end());

  const size_t size = students.size();
  char* result = new char[size + 1];
  size_t sch_code;
  while (!students.empty()) {
    stu = students.back();
    students.pop_back();
    for (int i = 0; i < 5; i++) {
      sch_code = size_t(stu.getVolunteer()[i] - 'a');
      if (schools[sch_code] > 0) {
        schools[sch_code]--;
        result[stu.getID()] = stu.getVolunteer()[i];
        break;
      }
      result[stu.getID()] = 'x';
    }
  }

  for (size_t i = 1; i <= size; i++)
    cout << i << ' ' << result[i] << endl;
  return 0;
}
