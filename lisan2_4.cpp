#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<vector<int>> mat(n, vector<int>(n));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> mat[i][j];
        }
    }
    bool reflexive = true;
    for (int i = 0; i < n; i++) {
        if (mat[i][i] != 1) {
            reflexive = false;
            break;
        }
    }
    if (!reflexive) {
        cout << "no" << endl;
        return 0;
    }
    bool symmetric = true;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (mat[i][j] != mat[j][i]) {
                symmetric = false;
                break;
            }
        }
        if (!symmetric) break;
    }
    if (!symmetric) {
        cout << "no" << endl;
        return 0;
    }
    bool transitive = true;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (mat[i][j] == 1) {
                for (int k = 0; k < n; k++) {
                    if (mat[j][k] == 1 && mat[i][k] != 1) {
                        transitive = false;
                        break;
                    }
                }
            }
            if (!transitive) break;
        }
        if (!transitive) break;
    }
    
    cout << (transitive ? "yes" : "no") << endl;
    return 0;
}