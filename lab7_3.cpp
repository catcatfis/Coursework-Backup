#include <iostream>
using namespace std;

class Vehicle {
public:
    int MaxSpeed;
    int Weight;
    Vehicle(int ms, int w) : MaxSpeed(ms), Weight(w) {
        cout << "Vehicle 构造函数执行" << endl;
    }
    ~Vehicle() {
        cout << "Vehicle 析构函数执行" << endl;
    }
    void Run() {
        cout << "Vehicle is running" << endl;
    }
    void Stop() {
        cout << "Vehicle stopped" << endl;
    }
};

class Bicycle : virtual public Vehicle {
public:
    int Height;
    Bicycle(int ms, int w, int h) : Vehicle(ms, w), Height(h) {
        cout << "Bicycle 构造函数执行" << endl;
    }
    ~Bicycle() {
        cout << "Bicycle 析构函数执行" << endl;
    }
};

class Motorcar : virtual public Vehicle {
public:
    int SeatNum;
    Motorcar(int ms, int w, int sn) : Vehicle(ms, w), SeatNum(sn) {
        cout << "Motorcar 构造函数执行" << endl;
    }
    ~Motorcar() {
        cout << "Motorcar 析构函数执行" << endl;
    }
};

class Motorcycle : public Bicycle, public Motorcar {
public:
    Motorcycle(int ms, int w, int h, int sn) 
        : Vehicle(ms, w), Bicycle(ms, w, h), Motorcar(ms, w, sn) {
        cout << "Motorcycle 构造函数执行" << endl;
    }
    ~Motorcycle() {
        cout << "Motorcycle 析构函数执行" << endl;
    }
};

int main() {
    Motorcycle m(80, 150, 120, 2); 
    m.Run();    
    m.Stop();   
    return 0;
}