#include <iostream>
#include <cstring>
using namespace std;

class People {
public:
    char name[20];
    int age;
    People(const char* n, int a) : age(a) {
        strcpy(name, n);
        cout << "People 构造函数执行" << endl;
    }
    ~People() {
        cout << "People 析构函数执行" << endl;
    }
    void Show() {
        cout << "Name: " << name << ", Age: " << age << endl;
    }
};

class Student : virtual public People {
public:
    char classNO[7];
    Student(const char* n, int a, const char* cn) : People(n, a) {
        strcpy(classNO, cn);
        cout << "Student 构造函数执行" << endl;
    }
    ~Student() {
        cout << "Student 析构函数执行" << endl;
    }
    void ShowStudent() {
        Show();
        cout << "ClassNO: " << classNO << endl;
    }
};

class Teacher : virtual public People {
public:
    char principalship[11];
    char department[21];
    Teacher(const char* n, int a, const char* p, const char* d) : People(n, a) {
        strcpy(principalship, p);
        strcpy(department, d);
        cout << "Teacher 构造函数执行" << endl;
    }
    ~Teacher() {
        cout << "Teacher 析构函数执行" << endl;
    }
    void ShowTeacher() {
        Show();
        cout << "Principalship: " << principalship << ", Department: " << department << endl;
    }
};

class Graduate : virtual public Student {
public:
    char subject[21];
    Teacher adviser;  
    Graduate(const char* n, int a, const char* cn, const char* sub, const char* an, int aa, const char* ap, const char* ad)
        : People(n, a), Student(n, a, cn), adviser(an, aa, ap, ad) {
        strcpy(subject, sub);
        cout << "Graduate 构造函数执行" << endl;
    }
    ~Graduate() {
        cout << "Graduate 析构函数执行" << endl;
    }
    void ShowGraduate() {
        ShowStudent();
        cout << "Subject: " << subject << endl;
        cout << "Adviser: ";
        adviser.ShowTeacher();
    }
};

class TA : public Graduate, public Teacher {
public:
    TA(const char* n, int a, const char* cn, const char* sub, const char* an, int aa, const char* ap, const char* ad)
        : People(n, a), Student(n, a, cn), Teacher(n, a, ap, ad), Graduate(n, a, cn, sub, an, aa, ap, ad) {
        cout << "TA 构造函数执行" << endl;
    }
    ~TA() {
        cout << "TA 析构函数执行" << endl;
    }
    void ShowTA() {
        ShowGraduate();
        ShowTeacher();
    }
};

int main() {
    TA ta("Alice", 24, "CS101", "Computer Science", "Prof.Wang", 40, "Professor", "CS Department");
    ta.ShowTA();
    return 0;
}