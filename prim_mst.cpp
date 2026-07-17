#include <iostream>
#include <vector>
#include <queue>
#include <functional>

using namespace std;

// 边结构：to 表示相邻顶点，weight 表示边权
struct Edge {
    int to;
    int weight;
};

// Prim 算法求无向连通图的最小生成树总权重
// 参数：
//   n      顶点数量，顶点编号为 1 到 n
//   graph  邻接表存储的无向带权图
// 返回：
//   若图连通，返回最小生成树权重；
//   若图不连通，返回 -1。
long long primMST(int n, const vector<vector<Edge>>& graph) {
    vector<bool> visited(n + 1, false);  // 标记顶点是否已经加入最小生成树

    // 小根堆：pair 的 first 是边权，second 是边连接到的顶点
    priority_queue<
        pair<int, int>,
        vector<pair<int, int>>,
        greater<pair<int, int>>
    > minHeap;

    long long totalWeight = 0; // 最小生成树总权重
    int selectedCount = 0;     // 已加入最小生成树的顶点数量

    // 从 1 号顶点开始构建最小生成树
    minHeap.push({0, 1});

    while (!minHeap.empty() && selectedCount < n) {
        int currentWeight = minHeap.top().first;
        int currentVertex = minHeap.top().second;
        minHeap.pop();

        // 如果该顶点已经加入最小生成树，则跳过
        if (visited[currentVertex]) {
            continue;
        }

        // 将当前顶点加入最小生成树
        visited[currentVertex] = true;
        totalWeight += currentWeight;
        selectedCount++;

        // 枚举当前顶点的所有邻边，把可选边加入小根堆
        for (const Edge& edge : graph[currentVertex]) {
            if (!visited[edge.to]) {
                minHeap.push({edge.weight, edge.to});
            }
        }
    }

    // 如果加入的顶点数量不足 n，说明原图不连通，不存在最小生成树
    if (selectedCount != n) {
        return -1;
    }

    return totalWeight;
}

int main() {
    int n, m;

    cout << "请输入顶点数 n 和边数 m：" << endl;
    cin >> n >> m;

    if (n <= 0 || m < 0) {
        cout << "输入错误：顶点数必须为正数，边数不能为负数。" << endl;
        return 0;
    }

    vector<vector<Edge>> graph(n + 1);

    cout << "请输入每条边的信息：起点 终点 权重" << endl;
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;

        if (u < 1 || u > n || v < 1 || v > n) {
            cout << "输入错误：顶点编号必须在 1 到 " << n << " 之间。" << endl;
            return 0;
        }

        // 无向图需要在两个方向都加入边
        graph[u].push_back({v, w});
        graph[v].push_back({u, w});
    }

    long long answer = primMST(n, graph);

    if (answer == -1) {
        cout << "该图不连通，不存在最小生成树。" << endl;
    } else {
        cout << "最小生成树的总权重为：" << answer << endl;
    }

    return 0;
}

/*
6 9
1 2 6
1 3 1
1 4 5
2 3 5
2 5 3
3 4 5
3 5 6
3 6 4
4 6 2
*/