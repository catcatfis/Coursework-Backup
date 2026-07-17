#include <iostream>
using namespace std;
#include <vector>
#include <algorithm>
#include <functional>
#include <string>
#include <ctime>


//random_shuffle    随机排序
void myPrint(int val){
    cout << val << " ";
}

void test01(){
    srand(unsigned(time(NULL)));

    vector<int> v1;
    for(int i = 0;i < 10;i++){
        v1.push_back(i);
    }

    random_shuffle(v1.begin(),v1.end());
    for_each(v1.begin(),v1.end(),myPrint);
    cout << endl;
}
int main(){
    test01();
    return 0;
}
