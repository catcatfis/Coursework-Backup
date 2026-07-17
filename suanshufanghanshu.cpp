#include <iostream>
using namespace std;
#include <functional>
void test01(){
    negate<int> n;//取反
    int a=n(10);
    cout<<"a="<<a<<endl;
}
void test02(){
    plus<int> p;
    int a=p(10,20);
    cout<<"a="<<a<<endl;
}
int main(){
    test01();
    test02();
    system("pause");
    return 0;
}