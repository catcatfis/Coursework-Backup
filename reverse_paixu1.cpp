#include  <iostream>
using namespace std;
#include <vector>
#include <algorithm>
#include <functional>
#include <string>

//reverse    反转

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
    for_each(v1.begin(),v1.end(),myPrint);
    cout << endl;

    reverse(v1.begin(),v1.end());
    for_each(v1.begin(),v1.end(),myPrint);
    cout << endl;

    
}
int main(){
    test01();
    system("pause");
    return 0;

}

