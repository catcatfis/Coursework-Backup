#include <iostream>
#include <bits/stdc++.h> 
#include <fstream>
#include <string>
using namespace std;
void test02(){
    ifstream ifs;
    ifs.open("test1.txt",ios::in);
    if(!ifs.is_open()){
        cout<<"打开失败"<<endl;
        return;
    }
    string buf;
    while(getline(ifs,buf)){
        cout<<buf<<endl;
    }
    ifs.close();
}
int main(){
    test02();
}