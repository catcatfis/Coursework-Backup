#include <iostream>
#include <vector>
#include <climits>
using namespace std;
int main(){
    int c;
    cin>>c;
    for(int i=0;i<c;i++)
    {
        int n;
        cin>>n;
        vector<int> a(n+1);
        for(int j=0;j<n+1;j++)
        {
            cin>>a[j];
        }
        vector<vector<int>> dp(n+1, vector<int>(n+1, 0));
        for(int len=2;len<=n;len++)
        {
            for(int i=1;i<=n-len+1;i++)
            {
                int j=i+len-1;
                dp[i][j]=INT_MAX;
                for(int k=i;k<j;k++)
                {
                    int cost=dp[i][k]+dp[k+1][j]+a[i-1]*a[k]*a[j];
                    if(cost<dp[i][j])
                    {
                        dp[i][j]=cost;
                    }
                }
            }
        }
        cout<<dp[1][n]<<endl;
    }
    return 0;
}