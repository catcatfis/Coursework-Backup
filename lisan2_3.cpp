#include <iostream>
#include <vector>
using namespace std;

int main() {
    int x, y;
    cin >> x >> y;
    vector<vector<int>> mat(x, vector<int>(y));
    for (int i = 0; i < x; i++) {
        for (int j = 0; j < y; j++) {
            cin >> mat[i][j];
        }
    }
    cout << endl;
    for (int j = 0; j < y; j++) {
        for (int i = 0; i < x; i++) {
            if (i > 0) cout << " ";
            cout << mat[i][j];
        }
        cout << endl;
    }
    return 0;
}