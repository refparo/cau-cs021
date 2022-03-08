#include <iostream>

using namespace std;

class GradeBook {
  string name, instructor;
public:
  GradeBook(string courseName, string instructorName) {
    name = courseName;
    instructor = instructorName;
  }
  string getInstructorName() const { return instructor; }
  void setInstructorName(string instructorName) { instructor = instructorName; }
  void displayMessage() {
    cout << "Welcome to the grade book for\n"
      << name << "!\n"
      << "This course is presented by: " << instructor << endl;
  }
};

//StudybarCommentBegin
int main() {
  GradeBook gradeBook(
    "CS101 Introduction to C++ Programming", "Professor Smith");
  cout << "gradeBook instructor name is: "
    << gradeBook.getInstructorName() << "\n";
  gradeBook.setInstructorName("Assistant Professor Bates");
  cout << "new gradeBook instructor name is: " 
    << gradeBook.getInstructorName() << "\n";
  gradeBook.displayMessage();
  return 0;
}
//StudybarCommentEnd
