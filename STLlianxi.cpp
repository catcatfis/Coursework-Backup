#include <iostream>
#include <string>
#include <vector>
#include <map>
using namespace std;
#define CHEHUA 0
#define MEISHU 1
#define YANFA 2
class Worker{
    public:
    string name;
    int salary;
};
void createWorkers(vector<Worker>& workers){
    string nameSeed="ABCDEFGHIJ";
    for(int i=0;i<10;i++){
        Worker w;
        w.name="worker";
        w.name+=nameSeed[i];
        w.salary=rand()%10000+10000;//10000~19999
        workers.push_back(w);
    }
}
void setGroup(vector<Worker>& vworker,multimap<int,Worker>& mWorker){
    for(vector<Worker>::iterator it=vworker.begin();it!=vworker.end();it++){
        int deptId=rand()%3;
        mWorker.insert(pair<int,Worker>(deptId,*it));
    }
}
void showGroup(multimap<int,Worker>& mWorker){
    cout<<"策划:"<<endl;
    multimap<int,Worker>::iterator pos=  mWorker.find(CHEHUA);
    int count=mWorker.count(CHEHUA);
    int index=0;
    for(;pos!=mWorker.end()&&index<count;pos++,index++){
        cout<<"name:   "<<pos->second.name<<"  salary:  "<<pos->second.salary<<endl;
    }
    cout<<"美术:"<<endl;
    pos=  mWorker.find(MEISHU);
    count=mWorker.count(MEISHU);
    index=0;
    for(;pos!=mWorker.end()&&index<count;pos++,index++){
        cout<<"name:   "<<pos->second.name<<"  salary:  "<<pos->second.salary<<endl;
    }
    cout<<"研发:"<<endl;
    pos=  mWorker.find(YANFA);
    count=mWorker.count(YANFA);
    index=0;
    for(;pos!=mWorker.end()&&index<count;pos++,index++){
        cout<<"name:   "<<pos->second.name<<"  salary:  "<<pos->second.salary<<endl;
    }
}
int main()
{
   vector<Worker> vworker;
   createWorkers(vworker);
   multimap<int,Worker> mWorker;
   setGroup(vworker,mWorker);
   for(multimap<int,Worker>::iterator it=mWorker.begin();it!=mWorker.end();it++){
    cout<<"name:   "<<it->second.name<<"  salary:  "<<it->second.salary<<endl;
   }
   showGroup(mWorker);
}