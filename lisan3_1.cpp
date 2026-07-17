#include <iostream>
using namespace std;

int main() {
    int degree;
    int sum = 0;
    cout << "请输入度数序列：" << endl;
    while (cin >> degree) {
        sum += degree;
    }
    int edges = sum / 2;
    cout << "边的条数: " << edges << endl;
    
    return 0;
}