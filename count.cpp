#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
//count 统计元素个数
//count_if 条件统计元素个数
class Person{
    public:
    Person(string name,int age){
        this->name=name;
        this->age=age;
    }
    string name;
    int age;
    bool operator==(const Person &p){
        if(this->age==p.age){
            return true;
        }
        else{
            return false;
        }
    }
    
};

void test01(){
    vector<int> v;
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);
    v.push_back(4);
    v.push_back(5);
    v.push_back(5);
    v.push_back(5);
    int num=count(v.begin(),v.end(),5);
    cout<<"5的个数为："<<num<<endl;
}
void test02(){
    vector<Person> v1;
    Person p1("张三",28);
    Person p2("李四",29);
    Person p3("王五",20);
    v1.push_back(p1);
    v1.push_back(p2);
    v1.push_back(p3);
    Person p4("赵六",28);
    v1.push_back(p4);

  
    int num = count(v1.begin(), v1.end(), p4) ;
    cout<<"28岁的人数为："<<num<<endl;

}


int main(){
    test01();
    test02();

    return 0;
}