#include <iostream>
using namespace std;
#include <vector>
#include <algorithm>
#include <functional>
void print(int i){
    cout<<i<<" ";
}
void test01(){
    vector<int> v;
    for(int i=0;i<10;i++){
        v.push_back(i);
    }
    for_each(v.begin(),v.end(),print);
}
int main(){
    test01();
    return 0;
}