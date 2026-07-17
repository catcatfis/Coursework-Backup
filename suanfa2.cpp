#include <iostream>
#include <vector>
#include <climits> // 用于 INT_MAX
using namespace std;
/**
 * 递归输出矩阵链乘的加括号方式
 * @param s 记录最优分割点的表
 * @param i 起始矩阵索引
 * @param j 结束矩阵索引
 */
void printOptimalParens(const vector<vector<int>>& s, int i, int j) {
    if (i == j) {
        cout << "A" << i;
    } else {
        cout << "(";
        printOptimalParens(s, i, s[i][j]);
        printOptimalParens(s, s[i][j] + 1, j);
        cout << ")";
    }
}

/**
 * 解决矩阵连乘问题
 * @param p 维度数组，矩阵 Ai 的维度为 p[i-1] x p[i]
 */
void matrixChainOrder(const vector<int>& p) {
    int n = p.size() - 1; // 矩阵的数量
    
    // m[i][j] 存储矩阵链 i 到 j 的最小乘法次数
    // s[i][j] 存储最优分割点 k
    // 大小均为 (n+1) * (n+1)，索引从 1 开始
    vector<vector<int>> m(n + 1, vector<int>(n + 1, 0));
    vector<vector<int>> s(n + 1, vector<int>(n + 1, 0));

    // l 为矩阵链的长度，从 2 到 n
    for (int l = 2; l <= n; l++) {
        // i 为起始位置
        for (int i = 1; i <= n - l + 1; i++) {
            int j = i + l - 1; // j 为结束位置
            m[i][j] = INT_MAX;
            
            // 尝试所有的分割点 k
            for (int k = i; k <= j - 1; k++) {
                // 计算当前分割的代价
                int q = m[i][k] + m[k + 1][j] + p[i - 1] * p[k] * p[j];
                
                // 如果代价更小，则更新
                if (q < m[i][j]) {
                    m[i][j] = q;
                    s[i][j] = k;
                }
            }
        }
    }

    cout << "最小标量乘法次数: " << m[1][n] << endl;
    cout << "最优加括号方案: ";
    printOptimalParens(s, 1, n);
    cout << endl;
}

int main() {
    int n;
    cout << "请输入矩阵的数量: ";
    cin >> n;

    // 矩阵维度数组 p 的长度为 n + 1
    // 例如有 3 个矩阵: A1(10x30), A2(30x5), A3(5x60)
    // 则 p 为 {10, 30, 5, 60}
    vector<int> p(n + 1);
    cout << "请按顺序输入 " << n + 1 << " 个维度值 (矩阵的行数和列数): ";
    for (int i = 0; i <= n; i++) {
        cin >> p[i];
    }

    matrixChainOrder(p);

    return 0;
}