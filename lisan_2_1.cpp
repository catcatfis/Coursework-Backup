#include <stdio.h>
#include <iostream>
#include <string.h>
#include <vector>
#include <algorithm>
#include <stack>
#include <map>
using namespace std;


int logical_NOT(int a) { return !a; }
int logical_AND(int a, int b) { return a && b; }
int logical_OR(int a, int b) { return a || b; }


vector<char> extractVariables(char a[]) {
    vector<char> vars;
    int len = strlen(a);
    
    for (int i = 0; i < len; i++) {
        if (a[i] >= 'A' && a[i] <= 'Z') {
            bool found = false;
            for (int j = 0; j < vars.size(); j++) {
                if (vars[j] == a[i]) {
                    found = true;
                    break;
                }
            }
            if (!found) {
                vars.push_back(a[i]);
            }
        }
    }
    
    sort(vars.begin(), vars.end());
    return vars;
}


string infixToPostfix(string expr) {
    stack<char> operators;
    string postfix = "";
    map<char, int> precedence;
    
   
    precedence['~'] = 3;  // 否定
    precedence['&'] = 2;  // 合取
    precedence['|'] = 2;  // 析取
    
    for (int i = 0; i < expr.length(); i++) {
        char c = expr[i];
        
        if (c >= 'A' && c <= 'Z') {
            postfix += c;
        }
        else if (c == '~') {
            operators.push(c);
        }
        else if (c == '&' || c == '|') {
         
            while (!operators.empty() && precedence[operators.top()] >= precedence[c]) {
                postfix += operators.top();
                operators.pop();
            }
            operators.push(c);
        }
    }
    
    
    while (!operators.empty()) {
        postfix += operators.top();
        operators.pop();
    }
    
    return postfix;
}


int evaluatePostfix(string postfix, int p, int q, int r) {
    stack<int> values;
    
    for (int i = 0; i < postfix.length(); i++) {
        char c = postfix[i];
        
        if (c >= 'A' && c <= 'Z') {
           
            if (c == 'P') values.push(p);
            else if (c == 'Q') values.push(q);
            else if (c == 'R') values.push(r);
            else values.push(0);
        }
        else if (c == '~') {
            
            int a = values.top(); values.pop();
            values.push(logical_NOT(a));
        }
        else if (c == '&') {
            
            int b = values.top(); values.pop();
            int a = values.top(); values.pop();
            values.push(logical_AND(a, b));
        }
        else if (c == '|') {
            
            int b = values.top(); values.pop();
            int a = values.top(); values.pop();
            values.push(logical_OR(a, b));
        }
    }
    
    return values.top();
}


string preprocessExpression(string expr) {
    string result = "";
    
    for (int i = 0; i < expr.length(); i++) {
        if (expr[i] == '~') {
            result += '~';
        }
        else if (expr[i] == '/' && i + 1 < expr.length() && expr[i + 1] == '\\') {
            result += '&';
            i++; // 跳过下一个字符
        }
        else if (expr[i] == '\\' && i + 1 < expr.length() && expr[i + 1] == '/') {
            result += '|';
            i++; // 跳过下一个字符
        }
        else if (expr[i] >= 'A' && expr[i] <= 'Z') {
            result += expr[i];
        }
    }
    
    return result;
}

int main() {
    char input[100];
    cout << "请输入合式公式: ";
    cin.getline(input, 100);
    
    string expr = input;
    
   
    vector<char> variables = extractVariables(input);
    int varCount = variables.size();
    
    if (varCount == 0) {
        cout << "未找到命题变元！" << endl;
        return 1;
    }
    
    if (varCount > 3) {
        cout << "变元数量超过3个，不支持！" << endl;
        return 1;
    }
    
    string processedExpr = preprocessExpression(expr);
    
    
    string postfix = infixToPostfix(processedExpr);
    
   
    for (int i = 0; i < varCount; i++) {
        cout << variables[i] << "\t";
    }
    cout << expr << endl;
    
    
    bool hasP = false, hasQ = false, hasR = false;
    
    for (int i = 0; i < varCount; i++) {
        if (variables[i] == 'P') hasP = true;
        if (variables[i] == 'Q') hasQ = true;
        if (variables[i] == 'R') hasR = true;
    }
    
    
    int rows = 1 << varCount; 
    
    for (int i = 0; i < rows; i++) {
        int p = 0, q = 0, r = 0;
        
        
        if (hasP) p = (i >> (varCount - 1)) & 1;
        if (hasQ) q = (i >> (varCount - (hasP ? 2 : 1))) & 1;
        if (hasR) r = (i >> (varCount - (hasP && hasQ ? 3 : (hasP || hasQ ? 2 : 1)))) & 1;
        
       
        if (varCount == 1) {
            if (hasP) cout << p << "\t";
            if (hasQ) cout << q << "\t";
            if (hasR) cout << r << "\t";
        }
        else if (varCount == 2) {
            if (hasP && hasQ) cout << p << "\t" << q << "\t";
            else if (hasP && hasR) cout << p << "\t" << r << "\t";
            else if (hasQ && hasR) cout << q << "\t" << r << "\t";
        }
        else if (varCount == 3) {
            cout << p << "\t" << q << "\t" << r << "\t";
        }
        
        
        int result = evaluatePostfix(postfix, p, q, r);
        cout << result << endl;
    }
    
    return 0;
}