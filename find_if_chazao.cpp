#include <iostream>
using namespace std;
#include <vector>
#include <algorithm>
#include <string>
#include <functional>
//find 查找元素
//find_if 条件查找
//binary_search 二分查找
//count 统计元素个数
//count_if 条件统计元素个数
class GreaterFive{
    public:
    bool operator()(int val){
        return val>5;
    }
};
class Person{
    public:
    Person(string name,int age){
        this->name=name;
        this->age=age;
    }

    string name;
    int age;
};
class Greater20{
    public:
    bool operator()(Person p){
        return p.age>20;
    }
};


void test01(){
    vector<int> v;
    for(int i=0;i<10;i++){
        v.push_back(i);
    }
    vector<int>::iterator it=find_if(v.begin(),v.end(),GreaterFive());
    if(it==v.end()){
        cout<<"未找到"<<endl;
    }
    else{
        cout<<"找到"<<*it<<endl;
    }
}


void test02(){
    vector<Person> v;
    Person p1("张三",28);
    Person p2("李四",29);
    Person p3("王五",20);
    v.push_back(p1);
    v.push_back(p2);
    v.push_back(p3);
    vector<Person>::iterator it=find_if(v.begin(),v.end(),Greater20());
    if(it==v.end()){
        cout<<"未找到"<<endl;
    }
    else{
        cout<<"找到"<<it->name<<endl;
    }
    cout<<"找到的人数为"<<count_if(v.begin(),v.end(),Greater20())<<endl;
}
int main(){
    test01();
    test02();

    return 0;
}

