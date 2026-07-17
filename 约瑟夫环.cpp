#include <iostream>
using namespace std;

// 定义链表节点结构
struct Node {
    int id;  // 人的编号
    int password;  // 人的密码
    Node* next;
    Node(int _id, int _password) : id(_id), password(_password), next(nullptr) {}
};

int main() {
    int n, m;
    cin >> n >> m;  // 输入人数和初始随机数

    // 创建循环链表
    Node* head = nullptr;
    Node* tail = nullptr;
    for (int i = 1; i <= n; ++i) {
        int password;
        cin >> password;
        Node* newNode = new Node(i, password);
        if (!head) {
            head = newNode;
            tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }
    }
    // 使链表成为循环链表
    tail->next = head;

    Node* prev = tail;
    Node* curr = head;
    while (curr->next != curr) {  // 当链表中不止一个节点时
        // 找到报数为 m 的节点
        for (int i = 1; i < m; ++i) {
            prev = curr;
            curr = curr->next;
        }
        cout << curr->id << " ";  // 输出出圈人的编号
        m = curr->password;  // 更新 m 为出圈人的密码
        // 删除出圈的节点
        prev->next = curr->next;
        Node* temp = curr;
        curr = curr->next;
        delete temp;
    }
    cout << curr->id << endl;  // 输出最后一个出圈人的编号
    delete curr;  // 释放最后一个节点的内存

    return 0;
}