#include <iostream>
using namespace std;
#include <algorithm>
#include <vector>
using namespace std;
//replace_if
class MyPrint
{
public:
    void operator()(int val)
    {
        cout<<val<<" ";
    }
};
class Greater30
{
public:
    bool operator()(int val)
    {
        return val>=30;
    }
};
void test01()
{
    vector<int> v;
    v.push_back(10);
    v.push_back(2);
    v.push_back(43);
    v.push_back(4);
    v.push_back(50);
    v.push_back(6);
    v.push_back(67);
    v.push_back(80);
    v.push_back(9);
    v.push_back(10);
    cout<<"替换前"<<endl;
    for_each(v.begin(),v.end(),MyPrint());
    cout<<endl;
    replace_if(v.begin(),v.end(),Greater30(),100);
    cout<<"替换后"<<endl;
    for_each(v.begin(),v.end(),MyPrint());
    cout<<endl;
}
int main()
{
   test01();
    return 0;
}
