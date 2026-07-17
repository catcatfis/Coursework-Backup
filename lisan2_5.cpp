#include <iostream>
#include <vector>
using namespace std;

int main() {
    int x, y, z;
    cin >> x >> y >> z;
    vector<vector<int>> R(x, vector<int>(y));
    vector<vector<int>> S(y, vector<int>(z));
    for (int i = 0; i < x; i++) {
        for (int j = 0; j < y; j++) {
            cin >> R[i][j];
        }
    }
    for (int j = 0; j < y; j++) {
        for (int k = 0; k < z; k++) {
            cin >> S[j][k];
        }
    }
    vector<vector<int>> res(x, vector<int>(z, 0));
    for (int i = 0; i < x; i++) {
        for (int k = 0; k < z; k++) {
            for (int j = 0; j < y; j++) {
                if (R[i][j] == 1 && S[j][k] == 1) {
                    res[i][k] = 1;
                    break;
                }
            }
        }
    }
    cout<<endl;
    for (int i = 0; i < x; i++) {
        for (int k = 0; k < z; k++) {
            if (k > 0) cout << " ";
            cout << res[i][k];
        }
        cout << endl;
    }
    return 0;
}