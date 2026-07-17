#include <iostream>
#include <vector>
#include <queue>
using namespace std;
bool isBipartite(int n, vector<vector<int>>& graph) {
    vector<int> color(n + 1, -1); 
    for (int i = 1; i <= n; i++) {
        if (color[i] == -1) { 
            queue<int> q;
            q.push(i);
            color[i] = 0; 
            while (!q.empty()) {
                int current = q.front();
                q.pop();
                for (int neighbor : graph[current]) {
                    if (color[neighbor] == -1) { 
                        color[neighbor] = 1 - color[current]; 
                        q.push(neighbor);
                    } else if (color[neighbor] == color[current]) {
                        return false;
                    }
                }
            }
        }
    }
    return true;
}

int main() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> graph(n + 1);
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u); 
    }
    bool result = isBipartite(n, graph);
    cout << (result ? 1 : 0) << endl;
    return 0;
}