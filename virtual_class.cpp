#include <iostream>

class Person {
  public:
    Person(int nPerson) {
      std::cout << "I am a Person" << nPerson << std::endl;
    }
    virtual ~Person() {
      std::cout << "Destroy Person Object" << std::endl;
    }

    virtual void* GetName() {
      std::cout << "Persion" << std::endl;
    }
};

class Student: virtual public Person {
  public:
    Student(int nStudent, int nPerson) 
      : Person(nPerson)
    {
      std::cout << "I am a student" << nStudent << std::endl;
    }
    ~Student() {
      std::cout << "Destroy Student Object" << std::endl;
    }

    void* GetName() {
      std::cout << "Student" << std::endl;
    }
};

class Teacher: virtual public Person {
  public: 
    Teacher(int nTeacher, int nPerson) 
      : Person(nPerson)
    {
      std::cout << "I am a teacher" << nTeacher << std::endl;
    }
    ~Teacher() {
      std::cout << "Destroy Teacher Oject" << std::endl;
    }

    void* GetName() {
      std::cout << "Teacher" << std::endl;
    }
};

class School: public Teacher, public Student
{
  public:
    School(int nStudent, int nTeacher, int nPerson) 
      : Student(nStudent, nPerson), Teacher(nTeacher, nPerson), Person(nPerson)
    {
      std::cout << "This is a school" << std::endl;
    }
    ~School() {
      std::cout << "Destroy School Object" << std::endl;
    }
    void* GetName() {
      std::cout << "School" << std::endl;
    }
};

int main() {

//  Student Yida;
//  Teacher Dan;
//  Yida.GetName();
//  Dan.GetName();
//  Person &per = Yida;
//  per.GetName();
  School UPenn(345, 564, 345+564);
  return 0;
}
