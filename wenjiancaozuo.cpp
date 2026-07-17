#include <iostream>
#include <bits/stdc++.h> 
#include <fstream>

using namespace std;

/*ios::in  为读文件而打开文件
ios::out  为写文件而打开文件 
ios::app 追加方式写文件
ios::ate 定位文件尾
ios::trunc 截断文件，如果文件存在，先删除文件内容再创建
ios::binary 二进制方式
用|可以同时打开多个模式
*/
void test01(){
   ofstream ofs;
   ofs.open("test.txt",ios::out);
   ofs<<"hello world"<<endl;
   ofs.close();
}
int main(){
  test01();
}