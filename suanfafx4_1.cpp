#include <iostream>
#include <vector>
#include <string>
using namespace std;
//动态规划最长公共子序列
int LCS(string X, string Y, int m, int n)
{
    vector<vector<int>> dp(m+1, vector<int>(n+1, 0));
    for(int i=1;i<=m;i++)
    {
        for(int j=1;j<=n;j++)
        {
            if(X[i-1]==Y[j-1])
            {
                dp[i][j]=dp[i-1][j-1]+1;
            }
            else
            {
                dp[i][j]=max(dp[i-1][j],dp[i][j-1]);
            }
        }
    }
    return dp[m][n];
}
int main()
{
    int c;
    cin>>c;
    for (int i = 0; i < c; i++)
    {
        string X, Y;
        cin>>X>>Y;
        int m = X.length();
        int n = Y.length();
        cout <<  LCS(X, Y, m, n) << endl;
    }
    
    return 0;
}