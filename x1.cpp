#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include <cmath>
using namespace std;

/**
 * 获取表示数值 val 所需的最小位数
 * 例如：5 (101) 需要 3 位，0 需要 1 位 (特殊处理)
 */
int get_bits_needed(int val) {
    if (val == 0) return 1;
    int bits = 0;
    while (val > 0) {
        val >>= 1;
        bits++;
    }
    return bits;
}

/**
 * 图像压缩求解函数
 * @param pixels 像素数组
 * @return 最小的总压缩位数
 */
void solveImageCompression(const vector<int>& pixels) {
    int n = pixels.size();
    
    // dp[i] 表示压缩前 i 个像素所需的最小位数
    vector<int> dp(n + 1, INT_MAX);
    // parent[i] 用于记录第 i 个像素划分时，当前段是从哪个位置开始的（用于回溯）
    vector<int> parent(n + 1, 0);

    // 基础情况
    dp[0] = 0;

    // 常量定义
    const int HEADER_BITS = 11; // 3位(表示位数) + 8位(表示长度)
    const int MAX_SEG_LEN = 255; // 每段最大长度

    // 动态规划求解
    for (int i = 1; i <= n; ++i) {
        int max_val = 0;
        
        // 遍历可能的段长度，从当前 i 往前推
        // 最多回溯 255 个位置
        for (int j = i - 1; j >= 0 && (i - j) <= MAX_SEG_LEN; --j) {
            // 更新当前片段 [j, i-1] 内的最大值
            max_val = max(max_val, pixels[j]);
            
            // 计算当前段的比特数
            // bits_per_pixel = 存储该段最大值需要的位数
            int bits_per_pixel = get_bits_needed(max_val);
            
            // 当前段总开销 = 头部开销(11) + (段长度 * 每个像素所需位数)
            int current_seg_cost = HEADER_BITS + (i - j) * bits_per_pixel;
            
            // 状态转移方程
            if (dp[j] != INT_MAX && dp[j] + current_seg_cost < dp[i]) {
                dp[i] = dp[j] + current_seg_cost;
                parent[i] = j; // 记录路径
            }
        }
    }

    // 输出结果
    cout << "最小压缩后的总位数: " << dp[n] << endl;

    // 回溯打印分段方案
    cout << "分段方案 (索引范围): " << endl;
    int curr = n;
    while (curr > 0) {
        int prev = parent[curr];
        cout << "[" << prev << ", " << curr - 1 << "] (值: ";
        for(int k = prev; k < curr; ++k) cout << pixels[k] << " ";
        cout << ")" << endl;
        curr = prev;
    }
}

int main() {
    // 示例输入: 一组像素值
    vector<int> pixels = {10, 12, 15, 255, 1, 2, 8, 9};

    cout << "原始像素序列: ";
    for (int p : pixels) cout << p << " ";
    cout << "\n----------------------------" << endl;

    solveImageCompression(pixels);

    return 0;
}