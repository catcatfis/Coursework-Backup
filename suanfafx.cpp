#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

template<typename Iterator>
bool my_next_permutation(Iterator first, Iterator last) {
    if (first == last) return false;
    
    Iterator i = last;
    --i;
    if (first == i) return false;
    
    while (true) {
        Iterator j = i;
        --i;
        if (*i < *j) {
            Iterator k = last;
            while (!(*i < *--k));
            iter_swap(i, k);
            reverse(j, last);
            return true;
        }
        if (i == first) {
            reverse(first, last);
            return false;
        }
    }
}

int main() {
    int n;
    cin >> n;
    string s;
    cin >> s;
    
    sort(s.begin(), s.end());
    
    int count = 0;
    do {
        cout << s << endl;
        count++;
    } while (my_next_permutation(s.begin(), s.end()));
    
    cout << count << endl;
    
    return 0;
}