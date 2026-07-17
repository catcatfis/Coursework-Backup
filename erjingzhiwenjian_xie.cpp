#include <bits/stdc++.h>
using namespace std;
#include <fstream>
class Person{
public:
    char name[20];
    int age;
};
void test01(){
    ofstream ofs;
    ofs.open("person.txt",ios::out | ios::binary);
    Person p={"张三",18};
    ofs.write(p.name,strlen(p.name));
    p.age = 18;
    ofs.write((const char *)&p,sizeof(Person));
    ofs.close();
}
int main(){
    test01();
    return 0;
}