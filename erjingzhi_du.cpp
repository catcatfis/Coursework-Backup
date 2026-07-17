#include <bits/stdc++.h>
using namespace std;
#include <fstream>
class Person{
public:
    char name[20];
    int age;
};
void test01(){
   ifstream ifs;
   ifs.open("person.txt",ios::in | ios::binary);
   if(!ifs.is_open()){
        cout<<"文件打开失败"<<endl;
        return;
    }
   Person p;
   ifs.read(p.name,strlen(p.name));
   ifs.read((char *)&p,sizeof(Person));
   cout<<p.name<<endl;
   cout<<p.age<<endl;
   ifs.close();
}
int main(){
    test01();
    return 0;
}