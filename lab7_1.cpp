#include <iostream>
using namespace std;

// 基类 Animal
class Animal {
public:  // 若改为 private，派生类无法直接访问 age
    int age;
};

// 派生类 Dog
class Dog : public Animal {
public:
    void SetAge(int n) {
        age = n;  // 直接给基类公有成员 age 赋值
    }
    void ShowAge() {
        cout << "Dog's age: " << age << endl;
    }
};

int main() {
    Dog dog;
    dog.SetAge(3);
    dog.ShowAge();
    return 0;
}