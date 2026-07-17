#include <iostream>
#include <set>
#include <string>
#include <sstream>
using namespace std;

// 解析输入字符串，返回元素集合
set<string> parseSet(string s) {
    set<string> res;
    // 去除首尾的{}
    s = s.substr(1, s.size() - 2);
    if (s.empty()) return res; // 空集
    stringstream ss(s);
    string elem;
    while (getline(ss, elem, ',')) {
        res.insert(elem);
    }
    return res;
}

int main() {
    string aStr, bStr;
    getline(cin, aStr);
    getline(cin, bStr);
    
    set<string> A = parseSet(aStr);
    set<string> B = parseSet(bStr);
    
    // 判断A是否为B的子集
    for (auto& elem : A) {
        if (B.find(elem) == B.end()) {
            cout << "No" << endl;
            return 0;
        }
    }
    cout << "Yes" << endl;
    return 0;
}