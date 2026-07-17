#include <iostream>
#include <algorithm>
#include <vector>
#include <numeric>
using namespace std;
//fill
//fill(iterator beg,iterator end,value)
//value是要填充的值
class MyPrint
{
public:
    void operator()(int val)
    {
        cout<<val<<" ";
    }
};
void test01()
{
    vector<int> v;
    v.resize(10);
    fill(v.begin(),v.end(),100);
    for_each(v.begin(),v.end(),MyPrint());
    cout<<endl;
}
int main()
{
    test01();
    return 0;
}
