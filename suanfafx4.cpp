#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;
 
int main() {
    int n;
    while (cin >> n) {
        vector<int> x, y;
        for (int i = 0; i < n; ++i) {
            int xi, yi;
            cin >> xi >> yi;
            x.push_back(xi);
            y.push_back(yi);
        }
        
        sort(x.begin(), x.end());
        sort(y.begin(), y.end());
        
        int median_x = x[n / 2];
        int median_y = y[n / 2];
        
        long long total_distance = 0;
        for (int i = 0; i < n; ++i) {
            total_distance += abs(x[i] - median_x) + abs(y[i] - median_y);
        }
        
        cout << total_distance << endl;
    }
    
    return 0;
}