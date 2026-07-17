#include <iostream>
using namespace std;
#include <vector>
#include <algorithm>
#include <functional>
//内建函数对象 ——逻辑仿函数
// logical_not 取反
// logical_and 逻辑与
// logical_or 逻辑或
void test01(){
    vector<bool> v;
    v.push_back(true);
    v.push_back(false);
    v.push_back(true);
    v.push_back(false);
    for(vector<bool>::iterator it=v.begin();it!=v.end();it++){
        cout<<*it<<" "<<endl;
    }
    cout<<"*******************"<<endl;
    vector<bool> v1;
    v1.resize(v.size());
    transform(v.begin(),v.end(),v1.begin(),logical_not<bool>());
    for(vector<bool>::iterator it=v1.begin();it!=v1.end();it++){
        cout<<*it<<" "<<endl;
    }
}
int main(){
    test01();
    return 0;
}