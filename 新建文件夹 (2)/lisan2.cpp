#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <map>
#include <stack>

using namespace std;

// 函数声明
vector<char> extractVariables(const string& formula);
bool evaluateFormula(const string& formula, const map<char, bool>& values);
bool isVariable(char c);
bool isOperator(char c);
int getPrecedence(char op);
vector<string> infixToPostfix(const string& formula);
bool evaluatePostfix(const vector<string>& postfix, const map<char, bool>& values);

int main() {
    string formula;
    cout << "请输入合式公式: ";
    cin >> formula;
    
    // 提取并排序变元
    vector<char> variables = extractVariables(formula);
    sort(variables.begin(), variables.end());
    
    // 输出表头，每一项用两个制表符分隔
    for (char var : variables) {
        cout << var << "\t";
    }
    cout << formula << endl;
    
    // 生成所有可能的真值组合
    int n = variables.size();
    for (int i = 0; i < (1 << n); i++) {
        map<char, bool> values;
        for (int j = 0; j < n; j++) {
            // 二进制位从右到左对应字典序的变元
            values[variables[n - 1 - j]] = (i >> j) & 1;
        }
        
        // 输出当前真值组合，每一项用两个制表符分隔
        for (char var : variables) {
            cout << (values[var] ? '1' : '0') << "\t";
        }
        
        // 计算并输出公式真值
        bool result = evaluateFormula(formula, values);
        cout << (result ? '1' : '0') << endl;
    }
    
    return 0;
}

// 提取公式中的所有变元
vector<char> extractVariables(const string& formula) {
    vector<char> variables;
    for (char c : formula) {
        if (isVariable(c) && find(variables.begin(), variables.end(), c) == variables.end()) {
            variables.push_back(c);
        }
    }
    return variables;
}

// 判断是否为变元
bool isVariable(char c) {
    return (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z');
}

// 判断是否为单字符运算符
bool isOperator(char c) {
    return c == '~' || c == '/' || c == '&';
}

// 获取运算符优先级
int getPrecedence(char op) {
    if (op == '~') return 3;
    if (op == '/' || op == '&') return 2;
    if (op == '-') return 1;
    if (op == '<') return 0;
    return -1;
}

// 将中缀表达式转换为后缀表达式
vector<string> infixToPostfix(const string& formula) {
    vector<string> postfix;
    stack<char> ops;
    
    for (size_t i = 0; i < formula.size(); i++) {
        char c = formula[i];
        
        if (isVariable(c)) {
            postfix.push_back(string(1, c));
        } 
        else if (c == '(') {
            ops.push(c);
        } 
        else if (c == ')') {
            while (!ops.empty() && ops.top() != '(') {
                postfix.push_back(string(1, ops.top()));
                ops.pop();
            }
            ops.pop(); // 弹出'('
        } 
        else if (c == '~') {
            ops.push(c);
        }
        else if (i + 1 < formula.size() && c == '-' && formula[i + 1] == '>') {
            // 处理 -> 运算符
            while (!ops.empty() && getPrecedence(ops.top()) >= getPrecedence('-')) {
                postfix.push_back(string(1, ops.top()));
                ops.pop();
            }
            ops.push('-'); // 用'-'表示->运算符
            i++; // 跳过 '>'
        }
        else if (i + 2 < formula.size() && c == '<' && formula[i + 1] == '-' && formula[i + 2] == '>') {
            // 处理 <-> 运算符
            while (!ops.empty() && getPrecedence(ops.top()) >= getPrecedence('<')) {
                postfix.push_back(string(1, ops.top()));
                ops.pop();
            }
            ops.push('<'); // 用'<'表示<->运算符
            i += 2; // 跳过 '-', '>'
        }
        else if (i + 1 < formula.size() && c == '/' && formula[i + 1] == '\\') {
            // 处理 \/ 运算符
            while (!ops.empty() && getPrecedence(ops.top()) >= getPrecedence('/')) {
                postfix.push_back(string(1, ops.top()));
                ops.pop();
            }
            ops.push('/'); // 用'/'表示\/运算符
            i++; // 跳过 '\'
        }
        else if (i + 1 < formula.size() && c == '&' && formula[i + 1] == '\\') {
            // 处理 /\ 运算符
            while (!ops.empty() && getPrecedence(ops.top()) >= getPrecedence('&')) {
                postfix.push_back(string(1, ops.top()));
                ops.pop();
            }
            ops.push('&'); // 用'&'表示/\运算符
            i++; // 跳过 '\'
        }
    }
    
    // 将剩余的运算符弹出
    while (!ops.empty()) {
        postfix.push_back(string(1, ops.top()));
        ops.pop();
    }
    
    return postfix;
}

// 计算后缀表达式的值
bool evaluatePostfix(const vector<string>& postfix, const map<char, bool>& values) {
    stack<bool> st;
    
    for (const string& token : postfix) {
        if (token.size() == 1 && isVariable(token[0])) {
            st.push(values.at(token[0]));
        } else if (token == "~") {
            bool val = st.top();
            st.pop();
            st.push(!val);
        } else if (token == "/") {
            bool val2 = st.top();
            st.pop();
            bool val1 = st.top();
            st.pop();
            st.push(val1 || val2);
        } else if (token == "&") {
            bool val2 = st.top();
            st.pop();
            bool val1 = st.top();
            st.pop();
            st.push(val1 && val2);
        } else if (token == "-") {
            bool val2 = st.top();
            st.pop();
            bool val1 = st.top();
            st.pop();
            st.push(!val1 || val2);
        } else if (token == "<") {
            bool val2 = st.top();
            st.pop();
            bool val1 = st.top();
            st.pop();
            st.push(val1 == val2);
        }
    }
    
    return st.top();
}

// 计算公式的值
bool evaluateFormula(const string& formula, const map<char, bool>& values) {
    vector<string> postfix = infixToPostfix(formula);
    return evaluatePostfix(postfix, values);
}