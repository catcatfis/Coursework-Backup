#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;
/**
 * 解决最长公共子序列 (LCS) 问题
 * @param s1 字符串1
 * @param s2 字符串2
 */
void solveLCS(const string& s1, const string& s2) {
    int n = s1.length();
    int m = s2.length();

    // 1. 初始化 DP 表
    // dp[i][j] 表示 s1 的前 i 个字符和 s2 的前 j 个字符的 LCS 长度
    // 大小为 (n+1) * (m+1)，初始化为 0
    vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));

    // 2. 状态转移计算
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            // 注意：s1 和 s2 的索引需要减 1，因为字符串是从 0 开始的
            if (s1[i - 1] == s2[j - 1]) {
                // 如果字符相等，LCS 长度加 1
                dp[i][j] = dp[i - 1][j - 1] + 1;
            } else {
                // 如果字符不相等，继承左方或上方较大的值
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
            }
        }
    }

    cout << "最长公共子序列长度为: " << dp[n][m] << endl;

    // 3. 回溯还原 LCS 字符串
    // 从 dp[n][m] 开始向左上回溯
    string lcs = "";
    int i = n, j = m;
    while (i > 0 && j > 0) {
        if (s1[i - 1] == s2[j - 1]) {
            // 字符匹配，说明该字符在 LCS 中
            lcs += s1[i - 1];
            i--;
            j--;
        } else if (dp[i - 1][j] >= dp[i][j - 1]) {
            // 上方的值大或相等，向上移动
            i--;
        } else {
            // 左方的值大，向左移动
            j--;
        }
    }

    // 因为是倒序回溯的，所以需要反转字符串
    reverse(lcs.begin(), lcs.end());
    cout << "最长公共子序列内容为: " << lcs << endl;
}

int main() {
    string s1, s2;
    cin >> s1;
    cin >> s2;
    solveLCS(s1, s2);
    return 0;
}