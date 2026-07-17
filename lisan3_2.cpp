#include <iostream>
#include <vector>
#include <queue>
using namespace std;
bool isConnected(const vector<vector<int>>& graph, int n) {
    if (n == 0) return true; 
    
    vector<bool> visited(n, false);
    queue<int> q;
    q.push(0);
    visited[0] = true;
    int count = 1; 
    
    while (!q.empty()) {
        int current = q.front();
        q.pop();
        
        for (int i = 0; i < n; i++) {
            if (graph[current][i] == 1 && !visited[i]) {
                q.push(i);
                visited[i] = true;
                count++;
            }
        }
    }
    return count == n;
}

int main() {
    int n;
    cout << "请输入无向图的结点个数：" << endl;
    cin >> n;
    
    vector<vector<int>> graph(n, vector<int>(n));
    cout << "请输入邻接矩阵：" << endl;
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> graph[i][j];
        }
    }
    
    if (isConnected(graph, n)) {
        cout << "Y" << endl;
    } else {
        cout << "N" << endl;
    }
    
    return 0;
}