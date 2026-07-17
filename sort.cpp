#include <iostream>
using namespace std;
#include <vector>
#include <algorithm>
#include <functional>

//sort排序
//random_shuffle    随机排序
//reverse  反转
//merge  合并
void myPrint(int val){
    cout << val << " ";
}

void test01(){
    vector<int> v1;
    v1.push_back(10);
    v1.push_back(70);
    v1.push_back(30);
    v1.push_back(60);
    v1.push_back(50);
    sort(v1.begin(),v1.end());
   for_each(v1.begin(),v1.end(),myPrint);
    cout << endl;
    sort(v1.begin(),v1.end(),greater<int>());
    for_each(v1.begin(),v1.end(),myPrint);
    cout << endl;


}
int main(){
    test01();
    return 0;
}



