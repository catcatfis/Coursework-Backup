#include <iostream>
#include <vector>
#include <string>
#include <stack>
#include <algorithm>
using namespace std;

// 计算表达式的值
bool calculateExpression(const string& expression, const vector<char>& vars, const vector<bool>& values) {
    stack<bool> stk;
    for (char c : expression) {
        if (c == '~') {
            bool val = stk.top();
            stk.pop();
            stk.push(!val);
        } else if (c == '/') {
            bool val2 = stk.top();
            stk.pop();
            bool val1 = stk.top();
            stk.pop();
            stk.push(val1 || val2);
        } else if (c == '\\') {
            bool val2 = stk.top();
            stk.pop();
            bool val1 = stk.top();
            stk.pop();
            stk.push(val1 && val2);
        } else if (c == '>') {
            bool val2 = stk.top();
            stk.pop();
            bool val1 = stk.top();
            stk.pop();
            stk.push(!val1 || val2);
        } else if (c == '<') {
            bool val2 = stk.top();
            stk.pop();
            bool val1 = stk.top();
            stk.pop();
            bool impl1 = !val1 || val2;
            bool impl2 = !val2 || val1;
            stk.push(impl1 && impl2);
        } else {
            for (int i = 0; i < vars.size(); ++i) {
                if (c == vars[i]) {
                    stk.push(values[i]);
                    break;
                }
            }
        }
    }
    return stk.top();
}

int main() {
    string expression;
    // 输入合式公式
    cin >> expression;

    vector<char> vars;
    // 提取命题变元
    for (char c : expression) {
        if (isalpha(c) && find(vars.begin(), vars.end(), c) == vars.end()) {
            vars.push_back(c);
        }
    }
    // 按字典序排序
    sort(vars.begin(), vars.end());

    int n = vars.size();
    // 输出命题变元
    for (char var : vars) {
        cout << var << " ";
    }
    cout << expression << endl;

    // 遍历所有可能的真值组合
    for (int i = 0; i < (1 << n); ++i) {
        vector<bool> values(n);
        for (int j = 0; j < n; ++j) {
            values[j] = (i >> (n - 1 - j)) & 1;
        }
        // 输出当前真值组合
        for (bool val : values) {
            cout << val << " ";
        }
        // 计算并输出表达式的值
        cout << calculateExpression(expression, vars, values) << endl;
    }

    return 0;
}