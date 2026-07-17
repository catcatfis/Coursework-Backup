#include <iostream>
using namespace std;
#include <vector>
#include <algorithm>
class GreaterFive{
    public:
    bool operator()(int a){
        return a>5;
    }
};
void test01(){
    vector <int> v;
    for(int i=0;i<10;i++){
        v.push_back(i);
    }
    vector<int>::iterator it= find_if(v.begin(),v.end(),GreaterFive());
    if(it!=v.end()){
        cout<<"找到大于5的数字"<<*it<<endl;
    }
    else{
        cout<<"未找到大于5的数字"<<endl;
    }
}
int main(){
    test01();
    return 0;
}