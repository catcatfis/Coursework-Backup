#include <iostream>
using namespace std;

class BaseClass {
public:
    BaseClass() {
        cout << "BaseClass 构造函数执行" << endl;
    }
    ~BaseClass() {
        cout << "BaseClass 析构函数执行" << endl;
    }
};

class DerivedClass : public BaseClass {
public:
    DerivedClass() {
        cout << "DerivedClass 构造函数执行" << endl;
    }
    ~DerivedClass() {
        cout << "DerivedClass 析构函数执行" << endl;
    }
};

int main() {
    DerivedClass dc;  
    system("pause");
    return 0;
}