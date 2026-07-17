#include <iostream>
using namespace std;
#include <vector>
#include <algorithm>
#include <functional>
#include <string>
//merge    合并排序（需要升降一致）
void myPrint(int val){
    cout << val << " ";
}

void test01(){
    vector<int> v1;
    vector<int> v2;
    for(int i = 0;i < 10;i++){
        v1.push_back(i);
        v2.push_back(i+1);
    }
    vector<int> v3;
    v3.resize(v1.size() + v2.size());
    merge(v1.begin(),v1.end(),v2.begin(),v2.end(),v3.begin());
    for_each(v3.begin(),v3.end(),myPrint);
    cout << endl;
}

int main(){
    test01();
    return 0;

}