
#include <iostream>
#include <list>
#include <thread>
#include <chrono>
#include <ctime>
using namespace std;

#include <Windows.h>

int nScreenWidth = 120;
int nScreenHeight = 30;

struct sSnakeSegment
{
    int x;
    int y;
};

int main()
{
    // Initialize random seed
    srand(static_cast<unsigned int>(time(nullptr)));

    // Create Screen Buffer
    wchar_t* screen = new wchar_t[nScreenWidth * nScreenHeight];
    for (int i = 0; i < nScreenWidth * nScreenHeight; i++) screen[i] = L' ';
    HANDLE hConsole = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
    SetConsoleActiveScreenBuffer(hConsole);
    DWORD dwBytesWritten = 0;

    while (1)
    {
        // Reset to known state
        list<sSnakeSegment> snake = { {60,15},{61,15},{62,15},{63,15},{64,15} };
        int nFoodX = 30;
        int nFoodY = 15;
        int nScore = 0;
        int nSnakeDirection = 3; // 0:Up, 1:Right, 2:Down, 3:Left
        bool bDead = false;
        bool bKeyLeft = false, bKeyRight = false, bKeyUp = false, bKeyDown = false;
        bool bKeyLeftOld = false, bKeyRightOld = false, bKeyUpOld = false, bKeyDownOld = false;
        int nSpeed = 150; // Initial speed (ms per move)

        while (!bDead)
        {
            // Frame Timing with adaptive speed based on score
            auto t1 = chrono::system_clock::now();
            while ((chrono::system_clock::now() - t1) < chrono::milliseconds(max(50, nSpeed - nScore * 2)))
            {
                // Get Input
                bKeyRight = (0x8000 & GetAsyncKeyState(VK_RIGHT)) != 0;
                bKeyLeft = (0x8000 & GetAsyncKeyState(VK_LEFT)) != 0;
                bKeyUp = (0x8000 & GetAsyncKeyState(VK_UP)) != 0;
                bKeyDown = (0x8000 & GetAsyncKeyState(VK_DOWN)) != 0;

                // Change direction based on key press, but prevent 180-degree turns
                if (bKeyRight && !bKeyRightOld && nSnakeDirection != 3)
                    nSnakeDirection = 1;
                if (bKeyLeft && !bKeyLeftOld && nSnakeDirection != 1)
                    nSnakeDirection = 3;
                if (bKeyUp && !bKeyUpOld && nSnakeDirection != 2)
                    nSnakeDirection = 0;
                if (bKeyDown && !bKeyDownOld && nSnakeDirection != 0)
                    nSnakeDirection = 2;

                bKeyRightOld = bKeyRight;
                bKeyLeftOld = bKeyLeft;
                bKeyUpOld = bKeyUp;
                bKeyDownOld = bKeyDown;
            }

            // ==== Logic

            // Update Snake Position
            switch (nSnakeDirection)
            {
            case 0: // UP
                snake.push_front({ snake.front().x, snake.front().y - 1 });
                break;
            case 1: // RIGHT
                snake.push_front({ snake.front().x + 1, snake.front().y });
                break;
            case 2: // DOWN
                snake.push_front({ snake.front().x, snake.front().y + 1 });
                break;
            case 3: // LEFT
                snake.push_front({ snake.front().x - 1, snake.front().y });
                break;
            }

            // Wrap around screen edges
            if (snake.front().x < 0) snake.front().x = nScreenWidth - 1;
            if (snake.front().x >= nScreenWidth) snake.front().x = 0;
            if (snake.front().y < 3) snake.front().y = nScreenHeight - 1;
            if (snake.front().y >= nScreenHeight) snake.front().y = 3;

            // Collision Detect Snake V Food
            if (snake.front().x == nFoodX && snake.front().y == nFoodY)
            {
                nScore++;
                // Generate new food position that's not on the snake
                bool bFoodValid = false;
                while (!bFoodValid)
                {
                    bFoodValid = true;
                    nFoodX = rand() % nScreenWidth;
                    nFoodY = (rand() % (nScreenHeight - 3)) + 3;
                    
                    // Check if food overlaps with snake
                    for (auto& segment : snake)
                    {
                        if (segment.x == nFoodX && segment.y == nFoodY)
                        {
                            bFoodValid = false;
                            break;
                        }
                    }
                }

                // Grow snake (don't remove tail this turn)
                for (int i = 0; i < 3; i++)
                    snake.push_back({ snake.back().x, snake.back().y });
            }
            else
            {
                // Only remove tail if didn't eat food
                snake.pop_back();
            }

            // Collision Detect Snake V Snake
            for (auto i = snake.begin(); i != snake.end(); ++i)
            {
                if (i != snake.begin() && i->x == snake.front().x && i->y == snake.front().y)
                    bDead = true;
            }

            // ==== Presentation

            // Clear Screen
            for (int i = 0; i < nScreenWidth * nScreenHeight; i++) screen[i] = L' ';

            // Draw Stats & Border
            for (int i = 0; i < nScreenWidth; i++)
            {
                screen[i] = L'=';
                screen[2 * nScreenWidth + i] = L'=';
            }
            swprintf(&screen[nScreenWidth + 5], nScreenWidth, L"www.OneLoneCoder.com - S N A K E ! !                SCORE: %d", nScore);

            // Draw Snake Body
            for (auto s : snake)
                screen[s.y * nScreenWidth + s.x] = bDead ? L'+' : L'O';

            // Draw Snake Head
            screen[snake.front().y * nScreenWidth + snake.front().x] = bDead ? L'X' : L'@';

            // Draw Food
            screen[nFoodY * nScreenWidth + nFoodX] = L'%';

            if (bDead)
                swprintf(&screen[15 * nScreenWidth + 40], nScreenWidth, L"    PRESS 'SPACE' TO PLAY AGAIN    ");

            // Display Frame
            WriteConsoleOutputCharacterW(hConsole, screen, nScreenWidth * nScreenHeight, { 0,0 }, &dwBytesWritten);
        }

        // Wait for space
        while ((0x8000 & GetAsyncKeyState(VK_SPACE)) == 0);
    }

    // Clean up (though this will never be reached due to infinite loop)
    delete[] screen;
    return 0;
}