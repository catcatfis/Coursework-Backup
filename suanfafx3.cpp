#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;
int main()
{
    int n;
    cin>>n;
    int a[n];
    for(int i=0;i<n;i++)
    {
        cin>>a[i];
    }
    for(int i=0;i<n;i++){
        int x=a[i]-2;
        int sum=0;
        for(int j=1;j<=x;j++){
            sum+=j;
        }
        sum++;
        cout<<sum<<endl;
    }
}