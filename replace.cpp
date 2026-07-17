#include <iostream>
using namespace std;
#include <vector>
#include <algorithm>
#include <functional>
#include <string>
//replace    替换
void myPrint(int val){
    cout << val << " ";
}

void test01(){
    vector<int> v1;
    v1.push_back(10);
    v1.push_back(90);
    v1.push_back(30);
    v1.push_back(70);
    v1.push_back(50);
    v1.push_back(30);
    for_each(v1.begin(),v1.end(),myPrint);
    cout << endl;
    replace(v1.begin(),v1.end(),30,3000);
    for_each(v1.begin(),v1.end(),myPrint);
    cout << endl;
}
int main(){
    test01();
    system("pause");
    return 0;
}

