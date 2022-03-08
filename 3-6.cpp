#include <iostream>

using namespace std;

class Account {
  double bal;
public:
  Account(double balance) {
    if (balance < 0) {
      cout << "\nError:Initial balance cannot be negative.\n\n";
      bal = 0;
    } else bal = balance;
  }
  double getBalance() const { return bal; }
  void credit(double amount) { bal += amount; }
  void debit(double amount) {
    if (amount > bal) cout << "Debit amount exceeded account balance.\n\n";
    else bal -= amount;
  }
};

//StudybarCommentBegin
int main() {
  Account account1(50.0);

  double withdrawalAmount;
  cin >> withdrawalAmount;
  cout << "\nattempting to subtract " << withdrawalAmount
       << " from account1 balance\n";

  account1.debit(withdrawalAmount);
  cout << "account1 balance:$" << account1.getBalance() << endl;

  Account account2(-2);
  cout << "account2 balance :$" << account2.getBalance() << endl;
  account2.credit(156.4);
  cout << "\nattempting to add " << 156.4 << " to account2\n";
  cout << "account2 balance :$" << account2.getBalance() << endl;

  return 0;
}
//StudybarCommentEnd
