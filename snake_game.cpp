#include <iostream>
#include <conio.h>
#include <windows.h>
#include <vector>
#include <ctime>

using namespace std;

// 定义方向枚举
enum Direction {
    STOP = 0,
    LEFT, RIGHT, UP, DOWN
};

// 定义坐标结构体
struct Point {
    int x;
    int y;
};

class SnakeGame {
private:
    int width;
    int height;
    bool gameOver;
    Direction dir;
    Point head;
    vector<Point> tail;
    Point food;
    int score;

public:
    SnakeGame(int w, int h) : width(w), height(h), gameOver(false), dir(STOP), score(0) {
        head.x = width / 2;
        head.y = height / 2;
        generateFood();
    }

    void generateFood() {
        food.x = rand() % width;
        food.y = rand() % height;
    }

    void draw() {
        system("cls");
        for (int i = 0; i < width + 2; i++)
            cout << "#";
        cout << endl;

        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                if (j == 0)
                    cout << "#";
                if (i == head.y && j == head.x)
                    cout << "O";
                else if (i == food.y && j == food.x)
                    cout << "F";
                else {
                    bool printed = false;
                    for (const auto& p : tail) {
                        if (p.x == j && p.y == i) {
                            cout << "o";
                            printed = true;
                            break;
                        }
                    }
                    if (!printed)
                        cout << " ";
                }
                if (j == width - 1)
                    cout << "#";
            }
            cout << endl;
        }

        for (int i = 0; i < width + 2; i++)
            cout << "#";
        cout << endl;
        cout << "Score: " << score << endl;
    }

    void input() {
        if (_kbhit()) {
            switch (_getch()) {
            case 'a':
                if (dir != RIGHT)
                    dir = LEFT;
                break;
            case 'd':
                if (dir != LEFT)
                    dir = RIGHT;
                break;
            case 'w':
                if (dir != DOWN)
                    dir = UP;
                break;
            case 's':
                if (dir != UP)
                    dir = DOWN;
                break;
            case 'x':
                gameOver = true;
                break;
            }
        }
    }

    void logic() {
        Point prev = head;
        for (size_t i = 0; i < tail.size(); i++) {
            Point temp = tail[i];
            tail[i] = prev;
            prev = temp;
        }

        switch (dir) {
        case LEFT:
            head.x--;
            break;
        case RIGHT:
            head.x++;
            break;
        case UP:
            head.y--;
            break;
        case DOWN:
            head.y++;
            break;
        case STOP:
            break;
        }

        if (head.x < 0 || head.x >= width || head.y < 0 || head.y >= height) {
            gameOver = true;
        }

        for (const auto& p : tail) {
            if (p.x == head.x && p.y == head.y) {
                gameOver = true;
            }
        }

        if (head.x == food.x && head.y == food.y) {
            score += 10;
            generateFood();
            tail.push_back(prev);
        }
    }

    bool isGameOver() const {
        return gameOver;
    }
};

int main() {
    std::srand(std::time(NULL));
    SnakeGame game(20, 10);

    while (!game.isGameOver()) {
        game.draw();
        game.input();
        game.logic();
        Sleep(100); // 控制游戏速度
    }

    cout << "Game Over!" << endl;
    return 0;
}