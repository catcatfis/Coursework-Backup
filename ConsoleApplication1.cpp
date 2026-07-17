#include <iostream>
using namespace std;
enum CPU_Rank{P1=1,P2,P3,P4,P5,P6,P7};
class CPU
{

private:
		int frequency;
		float voltage;
		CPU_Rank rank;
		
public:
	CPU(CPU_Rank r = P1, int f = 1000, float v = 1.2): rank(r),frequency(f),voltage(v) {
		cout << "构造函数被调用，等级：" << rank << "频率(MHZ)" << frequency << "电压（V) " << voltage << endl;
			r = rank;
			f = frequency;
			v = voltage;
		}
	CPU(const CPU& other) :rank(other.rank), frequency(other.frequency), voltage(other.voltage) {
		cout << "拷贝构造函数被调用" << endl;
	}
	~CPU() {
		cout << "析构函数被调用" << endl;
	}
	void run() {
		cout << "cpu 正在工作 等级" <<rank << "频率(MHZ)" << frequency << "电压（V) " << voltage << endl;
	}
	void stop() {
		cout << "cpu 停止工作" << endl;
	}
};

int main()
{
	 cout << "========== CPU类测试 ==========" << endl;
    
    // 测试构造函数
    cout << "\n1. 创建cpu1对象：" << endl;
    CPU cpu1(P3, 2500, 1.2);
    cpu1.run();
    cpu1.stop();
    
    cout << "\n2. 创建cpu2对象：" << endl;
    CPU cpu2(P5, 3200, 1.1);
    cpu2.run();
    cpu2.stop();
    
    cout << "\n3. 测试拷贝构造函数：" << endl;
    CPU cpu3 = cpu1;
    cpu3.run();
    
    cout << "\n4. 动态创建对象：" << endl;
    CPU* cpu4 = new CPU(P7, 4000, 1.3);
    cpu4->run();
    cpu4->stop();
    delete cpu4;
    
    cout << "\n========== 程序结束，观察析构顺序 ==========" << endl;
    return 0;
}
