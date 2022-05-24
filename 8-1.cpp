#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Review {
public:
  Review() {}
  bool fillReview();
  void showReview();
private:
  string title;
  int rating;
};

bool Review::fillReview() {
  getline(cin, title);
  if (title == "quit") return false;
  cin >> rating;
  if (!cin) return false;
  while (cin.get() != '\n') continue;
  return true;
}

void Review::showReview() {
  cout << rating << "\t" << title << endl;
}

int main() {
  vector<Review> books;
  Review temp;
  while (temp.fillReview())
    books.push_back(temp);
  int num = books.size();
  if (num > 0) {
    cout << "Thank you. You entered the following:\n"
      << "Rating\tBook\n";
    //使用下标，输出所有图书信息
    for (int i = 0; i < num; i++)
      books[i].showReview();
    cout << "Reprising:\n" << "Rating\tBook\n";
    vector<Review>::iterator pr;
    //使用迭代器，输出所有图书信息
    for (pr = books.begin(); pr != books.end(); pr++)
      pr->showReview();
    vector<Review> oldlist(books);
    if (num > 3) {
      // 删除第2和第3两条记录
      books.erase(books.begin() + 1, books.begin() + 3);
      cout << "After erasure:\n";
      //使用迭代器，输出所有图书信息
      for (pr = books.begin(); pr != books.end(); pr++)
        pr->showReview();
      // 将原来的（存储在oldlist中的）第2条记录插入到
      books.insert(books.begin(), oldlist.begin() + 1, oldlist.begin() + 2);
      cout << "After insertion:\n";
      //使用迭代器，输出所有图书信息
      for (pr = books.begin(); pr != books.end(); pr++)
        pr->showReview();
    }
    //利用oldlist恢复book中的信息。
    books.swap(oldlist);
    cout << "Swapping oldlist with books:\n";
    //使用迭代器，输出所有图书信息
    for (pr = books.begin(); pr != books.end(); pr++)
      pr->showReview();
  } else cout << "Nothing entered, nothing gained.\n";
  return 0;
}
