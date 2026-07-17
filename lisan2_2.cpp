#include <iostream>
#include <vector>
#include <string>
#include <sstream>
using namespace std;

int main() {
    string s;
    getline(cin, s);
    vector<string> elements;  
    cout<<endl;
    if (s.size() <= 2) {  
        cout << "{}" << endl;
        return 0;
    }
    string content = s.substr(1, s.size() - 2);  
    stringstream ss(content);
    string elem;
    while (getline(ss, elem, ',')) {
        elements.push_back(elem);  
    }
    
    int n = elements.size();
    for (int mask = 0; mask < (1 << n); ++mask) {  
        cout << "{";
        bool first = true;  
        for (int i = 0; i < n; ++i) {
            if (mask & (1 << i)) {
                if (!first) {
                    cout << ",";  
                }
                cout << elements[i];  
                first = false;
            }
        }
        cout << "}" << endl; 
    }
    
    return 0;
}