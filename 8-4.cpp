#include <iostream>
#include <string>

using namespace std;

string greet(
  string form,
  string lastname,
  string title, string::size_type pos, int length) {
  return form
    .replace(form.find("Daisy"), 5, lastname)
    .replace(form.find("Ms"), 2, title.substr(pos, length));
}

//StudybarCommentBegin
int main() {
  string generic1("Dear Ms Daisy:");
  string generic2("MrsMrMissPeople");
  string lastName("Annap");
  string salute = greet(generic1, lastName, generic2, 5, 4);

  cout << salute;
  return 0;
}
//StudybarCommentEnd
