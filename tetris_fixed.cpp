#include <iostream>
#include <thread>
#include <vector>
#include <stdio.h>
#include <Windows.h>
using namespace std;

int nScreenWidth = 80;
int nScreenHeight = 30;
wstring tetromino[7];
int nFieldWidth = 12;
int nFieldHeight = 18;
unsigned char* pField = nullptr;

// ... Rotate() 和 DoesPieceFit() 函数保持不变 ...

int main()
{
    // 新增控制台窗口设置
    HANDLE hConsole = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
    SetConsoleActiveScreenBuffer(hConsole);
    COORD bufferSize = { (short)nScreenWidth, (short)nScreenHeight };
    SetConsoleScreenBufferSize(hConsole, bufferSize);
    SMALL_RECT windowSize = { 0, 0, (short)nScreenWidth - 1, (short)nScreenHeight - 1 };
    SetConsoleWindowInfo(hConsole, TRUE, &windowSize);

    wchar_t* screen = new wchar_t[nScreenWidth * nScreenHeight];
    // ... 屏幕缓冲区初始化代码保持不变 ...

    // 游戏主循环
    while (!bGameOver)
    {
        // ... 定时和输入处理代码保持不变 ...

        // 修改后的旋转逻辑
        if (bKey[3] && bRotateHold)
        {
            int nNewRotation = (nCurrentRotation + 1) % 4;
            if (DoesPieceFit(nCurrentPiece, nNewRotation, nCurrentX, nCurrentY))
                nCurrentRotation = nNewRotation;
            bRotateHold = false;
        }

        // ... 其他游戏逻辑保持不变 ...

        // 修改得分显示缓冲区大小
        swprintf_s(&screen[2 * nScreenWidth + nFieldWidth + 6], 32, L"SCORE: %8d", nScore);

        // ... 显示逻辑保持不变 ...
    }

    // 清理资源
    CloseHandle(hConsole);
    cout << "Game Over!! Score:" << nScore << endl;
    delete[] screen;    // 新增内存释放
    delete[] pField;    // 新增内存释放
    system("pause");
    return 0;
}