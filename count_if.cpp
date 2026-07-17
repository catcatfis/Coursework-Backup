#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
class Greater20{
public:
    bool operator()(int val){
        return val > 20;
    }
};
class Person{
public:
    Person(string name,int age){
        this->m_Name = name;
        this->m_Age = age;
    }

    string m_Name;
    int m_Age;
};
class AgeGreater{
public:
    bool operator()(Person p){
        return p.m_Age > 20;
    }
};

void test01(){
    vector<int> v1;
    v1.push_back(10);
    v1.push_back(20);
    v1.push_back(30);
    v1.push_back(40);
    v1.push_back(50);
    int num = count_if(v1.begin(),v1.end(),Greater20());
    cout << "num = " << num << endl;

}
void test02(){
    vector<Person> v2;
    Person p1("张三",18);
    Person p2("李四",20);
    Person p3("王五",22);
    Person p4("赵六",24);
    Person p5("孙七",26);
    v2.push_back(p1);
    v2.push_back(p2);
    v2.push_back(p3);
    v2.push_back(p4);
    v2.push_back(p5);
    int num = count_if(v2.begin(),v2.end(),AgeGreater());
    cout << "num = " << num << endl;

}

int main(){
    test01();
    test02();
  
    return 0;
}
