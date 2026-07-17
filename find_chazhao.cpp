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
//adjacent_find 查找相邻重复元素
void test01(){
    //内置元素类型
    vector<int> v;
    for(int i=0;i<10;i++){
        v.push_back(i);
    }
    vector<int>::iterator it= find(v.begin(),v.end(),5);
    if(it==v.end()){
        cout<<"未找到"<<endl;
    }
    else{
        cout<<"找到"<<*it<<endl;
    }
}
//自定义元素类型
class Person{
    public:
    Person(string name,int age){
        this->name=name;
        this->age=age;
    }
    bool operator==(const Person& p){
        if(this->name==p.name&&this->age==p.age){
            return true;
        }
        else{
            return false;
        }
    }
        string name;
        int age;
};
void test02(){
    vector<Person> v;
    Person p1("张三",18);
    Person p2("李四",20);
    Person p3("王五",22);
    v.push_back(p1);
    v.push_back(p2);
    v.push_back(p3);
    Person pp("李四",20);

    vector<Person>::iterator it= find(v.begin(),v.end(),pp);
    if(it==v.end()){
        cout<<"未找到"<<endl;
    }
    else{
        cout<<"找到"<<it->name<<endl;
    }

}

int main(){
    test01();
    test02();

    return 0;
}
