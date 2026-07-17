#include <stdio.h>
#include <limits.h>

#define N 5  // 城市数量
#define INF INT_MAX

const char* city_names[N] = {"A", "B", "C", "D", "E"};

// 城市间距离矩阵（A=0, B=1, C=2, D=3, E=4）
int distance[N][N] = {
    {0, 3, 2, 9, 7},  // A
    {3, 0, 7, 2, 5},  // B
    {2, 7, 0, 9, 2},  // C
    {9, 2, 9, 0, 3},  // D
    {7, 5, 2, 3, 0}   // E
};

// 动态规划表：dp[mask][i] 表示从A出发，经过mask中的城市，最后到达i的最短距离
int dp[1 << N][N];

// 记录路径：parent[mask][i] 表示在状态(mask,i)的前一个城市
int parent[1 << N][N];

void tsp_dp() {
    int mask, i, j;

    // 初始化DP表
    for (mask = 0; mask < (1 << N); mask++) {
        for (i = 0; i < N; i++) {
            dp[mask][i] = INF;
            parent[mask][i] = -1;
        }
    }
    dp[1][0] = 0;  // 从A出发（mask=0b00001）

    // 动态规划填表
    for (mask = 1; mask < (1 << N); mask++) {
        for (i = 0; i < N; i++) {
            if (dp[mask][i] == INF) continue;  // 跳过不可达状态
            for (j = 0; j < N; j++) {
                if (!(mask & (1 << j))) {  // 如果城市j未访问
                    int new_mask = mask | (1 << j);
                    if (dp[new_mask][j] > dp[mask][i] + distance[i][j]) {
                        dp[new_mask][j] = dp[mask][i] + distance[i][j];
                        parent[new_mask][j] = i;  // 记录路径
                    }
                }
            }
        }
    }

    // 找到最短回路（最后返回A）
    int full_mask = (1 << N) - 1;
    int min_dist = INF;
    int last_city = -1;
    for (i = 1; i < N; i++) {
        if (dp[full_mask][i] + distance[i][0] < min_dist) {
            min_dist = dp[full_mask][i] + distance[i][0];
            last_city = i;
        }
    }

    // 回溯路径
    int path[N + 1];
    path[N] = 0;  // 最后回到A
    path[N - 1] = last_city;
    mask = full_mask;
    for (i = N - 2; i >= 0; i--) {
        path[i] = parent[mask][path[i + 1]];
        mask ^= (1 << path[i + 1]);  // 移除已回溯的城市
    }

    // 输出结果
    printf("最优路径: ");
    for (i = 0; i <= N; i++) {
        printf("%s ", city_names[path[i]]);
    }
    printf("\n最短距离: %d\n", min_dist);
}

int main() {
    tsp_dp();
    return 0;
}