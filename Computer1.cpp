#include <iostream>
using namespace std;
class CPU{
    public:
    virtual void caculate()=0; 
};
class VideoCard{
    public:
    virtual void display()=0; 
};
class Memory{
    public:
    virtual void storage()=0; 
};
class Computer{
    public:
    Computer(CPU * cpu,VideoCard* vc,Memory* mem){
        this->cpu=cpu;
        this->vc=vc;
        this->mem=mem;
    }
    void work(){
        cpu->caculate();
        vc->display();
        mem->storage();
    }
    ~Computer(){
        if(cpu!=NULL){
            delete cpu;
            cpu=NULL;
        }
        if(vc!=NULL){
            delete vc;
            vc=NULL;
        }
        if(mem!=NULL){
            delete mem;
            mem=NULL;
        }
    }
   private:
   CPU* cpu;
   VideoCard* vc;
   Memory* mem;
};
class IntelCPU:public CPU{
    public:
    void caculate(){
        cout<<"Intel CPU caculate"<<endl;
    }
};
class IntelVidioCard:public VideoCard{
    public:
    void display(){
        cout<<"Intel VideoCard display"<<endl;
    }
};
 class IntelMemory:public Memory{
    public:
    void storage(){
        cout<<"Intel Memory storage"<<endl;
    }
};
class LenovoCPU:public CPU{
    public:
    void caculate(){
        cout<<"Lenovo CPU caculate"<<endl;
    }
};
class LenovoVideoCard:public VideoCard{
    public:
    void display(){
        cout<<"Lenovo VideoCard display"<<endl;
    }
};
class LenovoMemory:public Memory{
    public:
    void storage(){
        cout<<"Lenovo Memory storage"<<endl;
    }
};
void test01(){
    cout<<"第一台电脑开始工作"<<endl;
    cout<<"------------------"<<endl;
    CPU* intelcpu=new IntelCPU();
    VideoCard* intelvc=new IntelVidioCard();
    Memory* intelmem=new IntelMemory();
    Computer* com1=new Computer(intelcpu,intelvc,intelmem);
    com1->work();
    delete com1;
    cout<<"第二台电脑开始工作"<<endl;
    cout<<"------------------"<<endl;
    Computer* com2=new Computer(new LenovoCPU,new LenovoVideoCard,new LenovoMemory);
    com2->work();
    delete com2;
}
int main(){
    test01();
    system("pause");
    return 0;                               
}