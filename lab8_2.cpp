#include <iostream>
using namespace std;
class Vehicle {
public:
    void Run() {
        cout << "Vehicle: 车辆启动" << endl;
    }
    void Stop() {
        cout << "Vehicle: 车辆停止" << endl;
    }
    // 虚函数版本
    /*
    virtual void Run() {
        cout << "Vehicle: 车辆启动" << endl;
    }
    virtual void Stop() {
        cout << "Vehicle: 车辆停止" << endl;
    }
    */
};

class Bicycle : public Vehicle {
public:
    void Run() {
        cout << "Bicycle: 自行车骑行" << endl;
    }
    void Stop() {
        cout << "Bicycle: 自行车停车" << endl;
    }
};

class Motorcar : public Vehicle {
public:
    void Run() {
        cout << "Motorcar: 汽车行驶" << endl;
    }
    void Stop() {
        cout << "Motorcar: 汽车刹车" << endl;
    }
};

class Motorcycle : public Bicycle, public Motorcar {
public:
    void Run() {
        cout << "Motorcycle: 摩托车飞驰" << endl;
    }
    void Stop() {
        cout << "Motorcycle: 摩托车熄火" << endl;
    }
};

int main() {
    Vehicle v;
    Bicycle b;
    Motorcar m;
    Motorcycle mc;
    cout << "直接调用对象的Run/Stop：" << endl;
    v.Run();  v.Stop();
    b.Run();  b.Stop();
    m.Run();  m.Stop();
    mc.Run(); mc.Stop();

    cout << "\n用Vehicle指针调用（非虚函数时，调用基类版本；虚函数时，调用派生类版本）：" << endl;
    Vehicle* pV = &v;
    pV->Run();  pV->Stop();

    pV = &b; 
    pV->Run();  pV->Stop(); 

    pV = &m; 
    pV->Run();  pV->Stop(); 
    return 0;
}