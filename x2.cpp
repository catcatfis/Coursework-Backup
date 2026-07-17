#include <iostream>
#include <vector>
#include <climits>
using namespace std;
/**
 * Prim算法实现最小生成树
 * 时间复杂度: O(V^2) 使用邻接矩阵，O(E log V) 使用优先队列
 * 空间复杂度: O(V^2) 存储邻接矩阵
 */
int main() {
    // 输入顶点数和边数
    int n, m;
    cout << "请输入顶点数和边数: ";
    cin >> n >> m;
    // 初始化邻接矩阵，INF表示不连通
    const int INF = INT_MAX;
    vector<vector<int>> graph(n, vector<int>(n, INF));
    // 输入每条边的信息
    cout << "请输入" << m << "条边的信息 (格式: u v w):" << endl;
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        // 假设是无向图，两个方向都要存储
        graph[u][v] = w;
        graph[v][u] = w;
    }
    // Prim算法核心数据结构
    vector<int> lowcost(n, INF);  // lowcost[i]表示顶点i到已生成树的最小距离
    vector<int> closest(n, -1);  // closest[i]表示顶点i距离已生成树最近的顶点
    vector<bool> visited(n, false);  // visited[i]表示顶点i是否已加入生成树
    // 从顶点0开始
    int start = 0;
    lowcost[start] = 0;
    int total_weight = 0;  // 最小生成树的总权重
    cout << "\nPrim算法执行过程:" << endl;
    cout << "=====================" << endl;
    // 执行n-1次，每次加入一个顶点
    for (int i = 0; i < n - 1; i++) {
        // 找到未访问顶点中lowcost最小的顶点
        int min_cost = INF;
        int k = -1;
        for (int j = 0; j < n; j++) {
            if (!visited[j] && lowcost[j] < min_cost) {
                min_cost = lowcost[j];
                k = j;
            }
        }
        // 将找到的顶点加入生成树
        if (k == -1) {
            cout << "图不连通，无法生成最小生成树!" << endl;
            return 0;
        }
        visited[k] = true;
        total_weight += lowcost[k];
        // 输出当前选择的边
        if (closest[k] != -1) {
            cout << "选择边: " << closest[k] << " - " << k 
                 << " (权重: " << lowcost[k] << ")" << endl;
        }
        // 更新其他未访问顶点到生成树的最小距离
        for (int j = 0; j < n; j++) {
            if (!visited[j] && graph[k][j] < lowcost[j]) {
                lowcost[j] = graph[k][j];
                closest[j] = k;
            }
        }
    }
    cout << "=====================" << endl;
    cout << "\n最小生成树的总权重: " << total_weight << endl;
    // 输出最小生成树的边
    cout << "\n最小生成树的边:" << endl;
    for (int i = 1; i < n; i++) {
        if (closest[i] != -1) {
            cout << closest[i] << " - " << i << " (权重: " 
                 << graph[closest[i]][i] << ")" << endl;
        }
    }
    
    return 0;
}