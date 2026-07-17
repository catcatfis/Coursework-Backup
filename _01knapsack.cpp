#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
    int n,m;
    cin>>n>>m;
    vector<int> v(n), w(n);
    for(int i=0;i<n;i++)
    {
        cin>>v[i];
    }
    for(int i=0;i<n;i++)
    {
        cin>>w[i];
    }
    vector<int> dp(m+1, 0);
    vector<vector<int>> choice(n, vector<int>(m+1, 0));    
    for(int i=0;i<n;i++)
    {
        for(int j=m;j>=w[i];j--)
        {
            if(dp[j-w[i]]+v[i] > dp[j]){
                dp[j] = dp[j-w[i]]+v[i];
                choice[i][j] = 1;
            }
        }
    }
    cout<<dp[m]<<endl;
    vector<int> isUsed(n, 0);
    int remaining = m;
    for(int i=n-1;i>=0;i--)
    {
        if(remaining >= w[i] && choice[i][remaining]){
            isUsed[i] = 1;
            remaining -= w[i];
        }
    }
    for (int i = 0; i < n; i++)
    {
        cout<<isUsed[i]<<" ";
    }
    cout<<endl;
    return 0;
}