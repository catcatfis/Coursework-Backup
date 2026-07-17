#include <iostream>
using namespace std;

class Point {
private:
    int _x, _y; 
public:
    Point(int x = 0, int y = 0) : _x(x), _y(y) {}
    Point& operator++() {
        _x++;
        _y++;
        return *this;
    }
    Point operator++(int) {
        Point temp = *this;
        _x++;
        _y++;
        return temp;
    }
    Point& operator--() {
        _x--;
        _y--;
        return *this;
    }

    Point operator--(int) {
        Point temp = *this;
        _x--;
        _y--;
        return temp;
    }

    void display() const {
        cout << "(" << _x << ", " << _y << ")" << endl;
    }
};

int main() {
    Point p(2, 3);
    cout << "初始坐标：";
    p.display();
    ++p;
    cout << "前置++后：";
    p.display();
    Point p2 = p++;
    cout << "后置++后（p的坐标）：";
    p.display();
    cout << "后置++返回的临时对象坐标：";
    p2.display();
    --p;
    cout << "前置--后：";
    p.display();
    Point p3 = p--;
    cout << "后置--后（p的坐标）：";
    p.display();
    cout << "后置--返回的临时对象坐标：";
    p3.display();

    return 0;
}