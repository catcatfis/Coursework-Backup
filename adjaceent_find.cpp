#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
//adjacent_find 查找相邻重复元素
void test01(){
    vector<int> v;
    v.push_back(1);
    v.push_back(2);
    v.push_back(2);
    v.push_back(4);
    v.push_back(0);
    v.push_back(6);
    v.push_back(7);
    v.push_back(8);
    v.push_back(8);
    v.push_back(10);
    
    vector<int>::iterator it=adjacent_find(v.begin(),v.end());
    if(it==v.end()){
        cout<<"未找到"<<endl;
    }
    else{
        cout<<"找到"<<*it<<endl;
    }
}

int main(){
    test01();

    return 0;
}
