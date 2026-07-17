#include <bits/stdc++.h>
using namespace std;
int a[100005];
int main(){
    int n;
    cin>>n;
    for(int i=0;i<n;i++){
        cin>>a[i];
    }
    int x=1e9;
    map<int,int> mp;
    for(int i=0;i<n;i++){
       x=min(x,a[i]);
       if(mp.find(a[i])==mp.end()){
           mp[a[i]]=1;
       }
       else{
           mp[a[i]]++;
       }
    }
    while(mp[x]>=x+1){
        if(mp[x]%(x+1)==0){
           if(mp.find(x+1)==mp.end()){
              mp[x+1]=0;
        }
        mp[x+1]+=mp[x]/(x+1);
        x+=1;
    }
    else{
        break;
    }
    }
    cout<<x<<endl;
    return 0;
}