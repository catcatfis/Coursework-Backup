#include <iostream>
using namespace std;

int main() {
    int v, e; 
    cout << "输入顶点数v和边数e：" << endl;
    cin >> v >> e;
    int r = e - v + 2;
    
    cout  << r << endl;
    return 0;
}