#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    int m;
    cin >> m;
    vector<int> b(m);
    for(int i = 0; i < m; i++) {
        cin >> b[i];
    }

    vector<int> c;
    int j = 0, k = 0;
    while (j < n && k < m) {
        if (a[j] < b[k]) {
            c.push_back(a[j]);
            j++;
        } else if (a[j] > b[k]) {
            c.push_back(b[k]);
            k++;
        } else {
            c.push_back(a[j]);
            j++;
            k++;
        }
    }
    while (j < n) {
        c.push_back(a[j]);
        j++;
    }
    while (k < m) {
        c.push_back(b[k]);
        k++;
    }
    for (int num : c) {
        cout << num << " ";
    }

    return 0;
}