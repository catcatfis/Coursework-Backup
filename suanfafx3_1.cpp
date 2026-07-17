#include <iostream>
using namespace std;
int main()
{
    int c;
    cin>>c;
    for(int i=0;i<c;i++)
    {
        int n;
        cin>>n;
        int a[n];
        for(int j=0;j<n;j++)
        {
            cin>>a[j];
        }
        //动态规划最大子段和
        int max_sum=a[0];
        int sum=0;
        for(int j=0;j<n;j++)
        {
            sum+=a[j];
            if(sum>max_sum)
            {
                max_sum=sum;
            }
            if(sum<0)
            {
                sum=0;
            }
        }
        if(max_sum<0)
        {
            max_sum=0;
        }
        cout<<max_sum<<endl;
    }
    return 0;
}