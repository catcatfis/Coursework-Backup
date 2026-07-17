#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
int main()
{
	int n;
	cin>>n;
	int m;
	cin>>m;
	 int a[n];
     int t;
     int c;
     for(int i=0;i<n;i++)
     {
         cin>>a[i];
     }
     int *p=a;
     for(int i=0;i<n;i++){
     for(int j=0;j<m;j++)
     {if(p<&a[n]){
        while(*p==0){
        p++;
                    }
    }
    else{
        p=a;
        for(int j=1;j<m;j++){
        	while(*p==0){
                p++;
                }
    }
    }
    }
t=*p;
*p=0;
m=t;
cout <<p-a<<" ";
     }
}