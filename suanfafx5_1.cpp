#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
using namespace std;

struct Item {
    int weight;
    int value;
    double ratio;
    int index;
};

bool compareItems(const Item& a, const Item& b) {
    return a.ratio > b.ratio;
}

int main(){
    
    int n,c;
    cin>>n>>c;
    vector<int> w(n+1),v(n+1);
    for(int i=1;i<=n;i++)
    {
        cin>>w[i];
    }
    for (int i=1;i<=n;i++)
    {
       cin>>v[i];
    }
    
    vector<Item> items(n);
    for(int i=0;i<n;i++) {
        items[i].weight = w[i+1];
        items[i].value = v[i+1];
        items[i].ratio = (double)v[i+1] / w[i+1];
        items[i].index = i+1;
    }
    
    sort(items.begin(), items.end(), compareItems);
    
    double totalValue = 0.0;
    int remainingCapacity = c;
    
    for(int i=0;i<n;i++) {
        if(remainingCapacity <= 0) break;
        
        int takeWeight = min(items[i].weight, remainingCapacity);
        double takeValue = takeWeight * items[i].ratio;
        totalValue += takeValue;
        remainingCapacity -= takeWeight;
    }
    
    cout<<fixed<<setprecision(1) << totalValue << endl;
    
    return 0;
}