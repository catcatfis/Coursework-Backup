#include <iostream>
#include <string>
#include <vector>
#include <map>
using namespace std;

class Myadd{
    public:
    int operator()(int a,int b){
        return a+b;
    }
};
void test01(){
    Myadd myadd;
    int ret=myadd(10,20);
    cout<<"ret="<<ret<<endl;
}
class Myprint{
    public:
    void operator()(string test){
        cout<<test<<endl;
    }
};
void test02(){
    Myprint myprint;
    myprint("hello world");
}
int main(){
    test01();
    test02();
    return 0;
}