#include <iostream>
#include <algorithm>
#include <vector>
#include <numeric>
using namespace std;
//accuminate
//accumulate(iterator beg,iterator end,value)
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
    for(int i=0;i<=100;i++)
    {
        v.push_back(i);
    }
    int total=accumulate(v.begin(),v.end(),0);//计算v的总和，0是起始累加值
    cout<<"total="<<total<<endl;



}
int main()
{
    test01();
    return 0;
}
