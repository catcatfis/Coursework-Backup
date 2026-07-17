#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;
 int main()
 {
     int n;
     cin>>n;
     long long x;
     cin>>x;
     vector<long long> a(n);
        for(int i=0;i<n;i++)
        {
            cin>>a[i];
        }
        sort(a.begin(),a.end());
        int mid=n/2;
        int left=0;
        int right=n-1;
        int count=0;
        while(left<right)
        {
            if(a[mid]==x)
            {
                cout<<mid<<endl;
                break;
            }
            else if(a[mid]>x)
            {
                right=mid-1;
            }
            else
            {
                left=mid+1;
            }
            mid=(left+right)/2;
        }
        while(a[mid]==x)
        {
            count++;
            mid++;
        }
        cout<<x<<" "<<count<<endl;
 }