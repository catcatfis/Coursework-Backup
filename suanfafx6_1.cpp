#include <iostream>
#include <algorithm>
using namespace std;
struct Activity
{
    int start, end;
};
bool compare(Activity a, Activity b) {
    return a.end < b.end;
}
int main() {
    int k;
    while (cin >> k) {
        Activity activities[1000];
        for (int i = 0; i < k; i++) {
            cin >> activities[i].start >> activities[i].end;
        }
        
        sort(activities, activities + k, compare);
        
        int count = 1;
        int lastEnd = activities[0].end;
        
        for (int i = 1; i < k; i++) {
            if (activities[i].start >= lastEnd) {
                count++;
                lastEnd = activities[i].end;
            }
        }
        
        cout << count << endl;
    }
    return 0;
}