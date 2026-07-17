#include <iostream>
#include <fstream>
#include <string>       // 新增string头文件
#include <filesystem>   // 新增文件系统库

using namespace std;
using namespace std::filesystem; // 添加文件系统命名空间

void test02(){
    const path file_path = "test.txt"; // 使用文件系统路径类型
    
    // 添加文件存在性检查
    if (!exists(file_path)) {
        cerr << "错误：文件不存在" << endl;
        return;
    }

    ifstream ifs(file_path);
    if(!ifs.is_open()){
        cerr << "打开文件失败：";  // 改用cerr输出错误
        perror("");              // 添加系统错误信息
        return;
    }

    string line; // 改用string代替字符数组
    while(getline(ifs, line)) {  // 使用getline读取整行
        cout << line << endl;
    }
    
    ifs.close();
}

// ... 保持main函数不变 ...