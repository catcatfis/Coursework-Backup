#include <iostream>
#include <string>
using namespace std;
enum CPU_Rank {P1 = 1, P2, P3, P4, P5, P6, P7};
class CPU
{

private:
		int frequency;
		float voltage;
		CPU_Rank rank;
		
public:
	CPU(CPU_Rank r = P1, int f = 1000, float v = 1.2): rank(r),frequency(f),voltage(v) {
		cout << "CPU 构造函数被调用，等级：" << rank << "频率(MHZ)" << frequency << "电压（V) " << voltage << endl;
			r = rank;
			f = frequency;
			v = voltage;
		}
	CPU(const CPU& other) :rank(other.rank), frequency(other.frequency), voltage(other.voltage) {
		cout << "CPU拷贝构造函数被调用" << endl;
	}
	~CPU() {
		cout << "CPU析构函数被调用" << endl;
	}
	void run() {
		cout << "cpu 正在工作 等级" <<rank << "频率(MHZ)" << frequency << "电压（V) " << voltage << endl;
	}
	void stop() {
		cout << "cpu 停止工作" << endl;
	}
};

class RAM {
private:
    int capacity;  
public:
    RAM(int c = 4) : capacity(c) {
        cout << "RAM 构造函数被调用 - 容量:" << capacity << "GB" << endl;
    }
    
    ~RAM() {
        cout << "RAM 析构函数被调用" << endl;
    }
    
    void run() {
        cout << "RAM运行中... 容量:" << capacity << "GB" << endl;
    }
    
    void stop() {
        cout << "RAM已停止" << endl;
    }
};

class CDROM {
private:
    string type;
public:
    CDROM(string t = "DVD") : type(t) {
        cout << "CDROM 构造函数被调用 - 类型:" << type << endl;
    }
    
    ~CDROM() {
        cout << "CDROM 析构函数被调用" << endl;
    }
    
    void run() {
        cout << "CDROM运行中... 类型:" << type << endl;
    }
    
    void stop() {
        cout << "CDROM已停止" << endl;
    }
};

class Computer {
private:
    CPU cpu;
    RAM ram;
    CDROM cdrom;
public:

    Computer(CPU c, RAM r, CDROM cd) : cpu(c), ram(r), cdrom(cd) {
        cout << "Computer 构造函数被调用" << endl;
    }
    
    Computer(CPU_Rank cr = P4, int ramSize = 8, string cdType = "DVD") 
        : cpu(cr), ram(ramSize), cdrom(cdType) {
        cout << "Computer 默认参数构造函数被调用" << endl;
    }
    
    ~Computer() {
        cout << "Computer 析构函数被调用" << endl;
    }
    
    void run() {
        cout << "\n=== 计算机启动 ===" << endl;
        cpu.run();
        ram.run();
        cdrom.run();
        cout << "=== 所有组件运行正常 ===" << endl;
    }
    
    void stop() {
        cout << "\n=== 计算机关闭 ===" << endl;
        cdrom.stop();
        ram.stop();
        cpu.stop();
        cout << "=== 计算机已完全关闭 ===" << endl;
    }
};

int main() {
    cout << "========== Computer类测试 ==========" << endl;
    
    cout << "\n1. 测试组合对象的构造顺序：" << endl;
    {
        Computer comp1;
        comp1.run();
        comp1.stop();
    }
    
    cout << "\n2. 测试带参数的构造函数：" << endl;
    {
        Computer comp2(P6, 16, "Blu-ray");
        comp2.run();
        comp2.stop();
    }
    
    cout << "\n3. 测试手动创建组件：" << endl;
    {
        CPU myCpu(P5, 3000, 1.2);
        RAM myRam(32);
        CDROM myCdrom("CD-RW");
        
        Computer comp3(myCpu, myRam, myCdrom);
        comp3.run();
        comp3.stop();
    }
    
    cout << "\n========== 程序结束 ==========" << endl;
    return 0;
}