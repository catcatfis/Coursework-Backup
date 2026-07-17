#include<iostream>
using namespace std;
int main()
{
    bool p,q;
    bool x=1,y=1;
    cin>>p>>q;
    cout << "P"<< "\tQ"<<"\t~P"<<"\t~Q"<<"\tP^Q" <<"\tPvQ" <<"\tP->Q" <<"\tP"<<"<"<<"-"<<">Q" << endl;
    if(p=1&&q==0)
    {
        x=0;
    }
    if((p==0&&q==1)||(p==1&&q==0))
    {
        y=0;
    }
    cout<<p<<"\t"<<q<<"\t"<<!p<<"\t"<<!q<<"\t"<<(p&q)<<"\t"<<(p||q)<<"\t"<<x<<"\t"<<y<<endl;
    return 0;
}