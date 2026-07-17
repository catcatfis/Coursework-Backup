#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
//swap替换
class MyPrint
{
public:
    void operator()(int val)
    {
        cout<<val<<" ";
    }
};

void test01(){
    vector<int> v1;
    vector<int> v2;
    v1.push_back(10);
    v1.push_back(20);
    v1.push_back(30);
    v1.push_back(40);
    v1.push_back(50);
    v2.push_back(100);
    v2.push_back(200);
    v2.push_back(300);
    v2.push_back(400);
    v2.push_back(500);
    cout<<"替换前"<<endl;
    for_each(v1.begin(),v1.end(),MyPrint());
    cout<<endl;
    for_each(v2.begin(),v2.end(),MyPrint());
    cout<<endl;
    v1.swap(v2);//swap(v1,v2)

    cout<<"替换后"<<endl;
    for_each(v1.begin(),v1.end(),MyPrint());
    cout<<endl;
    for_each(v2.begin(),v2.end(),MyPrint());
    cout<<endl;

}
int main(){
    test01();
    return 0;
}