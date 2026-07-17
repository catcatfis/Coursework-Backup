#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
//binary_search 二分查找(容器必须有序，若无序结果未知)


void test01(){
    vector<int> v;
    for(int i=0;i<10;i++){
        v.push_back(i);
    }
    //二分查找
    bool ret=binary_search(v.begin(),v.end(),7);
    if(ret){
        cout<<"找到"<<endl;
    }
    else{
        cout<<"未找到"<<endl;
    }

}
int main(){
    test01();
    return 0;
}
