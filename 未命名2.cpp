#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
#define MAXSIZE 20

typedef int Status;
typedef int ElemType;

// 定义链表节点结构
typedef struct LNode {
    ElemType data;
    struct LNode* next;
} LNode, *LinkList;

// 比较函数，用于 LocateElem
Status eq(ElemType a, ElemType b) {
    return a == b;
}

// 初始化链表
Status InitList(LinkList& L) {
    if (L) delete L; // 防止内存泄漏
    L = new LNode;
    L->next = NULL;
    return OK; 
}

// 打印链表
void display(LinkList L) {
    LNode* p = L->next;
    while (p) {
        cout << p->data << " ";
        p = p->next;
    }
    cout << endl;
}

// 判断链表是否为空
Status ListEmpty(LinkList L) {
    if (L->next) {
        cout << "非空" << endl; 
        return FALSE;
    } else {
        cout << "空" << endl; 
        return TRUE;
    }
}

// 获取链表长度
Status ListLength(LinkList L) {
    int length = 0;
    LNode* p = L->next;
    while (p) {
        length++;
        p = p->next;
    }
    cout << "链表长度为: " << length << endl; 
    return length;
}

// 按序号查找元素
Status GetElem(LinkList L, int i, ElemType& e) {
    LNode* p = L->next;
    int j = 1;
    while (p && j < i) {
        p = p->next;
        ++j; 
    } 
    if (!p || j > i) return ERROR;
    e = p->data;
    return OK;
}

// 按值查找元素
Status LocateElem(LinkList L, ElemType e, Status(*eq)(ElemType, ElemType)) {
    LNode* p = L->next;
    int j = 1;
    while (p && !eq(p->data, e)) {
        p = p->next;
        ++j;
    }
    if (p) return j;
    else return ERROR; 
}

// 插入元素
Status ListInsert(LinkList& L, int i, ElemType e) {
    LNode* p = L;
    int j = 0;
    while (p && j < i - 1) {
        p = p->next;
        ++j;
    } 
    if (!p || j > i - 1) return ERROR;
    LNode* s = new LNode;
    s->data = e;
    s->next = p->next;
    p->next = s;
    return OK;
}

// 删除元素
Status ListDelete(LinkList& L, int i, ElemType& e) {
    LNode* p = L;
    int j = 0;
    while (p->next && j < i - 1) {
        p = p->next;
        ++j;
    }
    if (!p->next || j > i - 1) return ERROR;
    LNode* q = p->next;
    p->next = q->next;
    e = q->data;
    delete q;
    return OK; 
}

int main() {
    LinkList L = NULL; // 初始化链表指针
    ElemType e;        // 用于存储元素值
    int i;             // 用于存储序号
    int n;             // 用于选择功能序号

    while (1) {
        cout << "1初始化 2打印 3 判空 4 求长度 5 按序号查找 6 按值查找 7 插入 8 删除" << endl;
        cout << "请选择功能序号：" << endl;
        cin >> n;

        switch (n) {
            case 1:
                InitList(L);
                break;
            case 2:
                display(L);
                break;
            case 3:
                ListEmpty(L);
                break;
            case 4:
                ListLength(L);
                break;
            case 5:
                cout << "请输入序号 i: ";
                cin >> i;
                if (GetElem(L, i, e) == OK) {
                    cout << "第 " << i << " 个元素的值为: " << e << endl;
                } else {
                    cout << "查找失败" << endl;
                }
                break;
            case 6:
                cout << "请输入要查找的值 e: ";
                cin >> e;
                i = LocateElem(L, e, eq);
                if (i != ERROR) {
                    cout << "值 " << e << " 的位置为: " << i << endl;
                } else {
                    cout << "未找到该值" << endl;
                }
                break;
            case 7:
                cout << "请输入插入位置 i 和插入值 e: ";
                cin >> i >> e;
                if (ListInsert(L, i, e) == OK) {
                    cout << "插入成功" << endl;
                } else {
                    cout << "插入失败" << endl;
                }
                break;
            case 8:
                cout << "请输入删除位置 i: ";
                cin >> i;
                if (ListDelete(L, i, e) == OK) {
                    cout << "删除成功，删除的元素为: " << e << endl;
                } else {
                    cout << "删除失败" << endl;
                }
                break;
            default:
                cout << "无效的选项，请重新输入！" << endl;
                break;
        }

        cout << "是否继续其他操作？Y（1）N（0）" << endl;
        cin >> n;
        if (n == 0) break;
    }

    // 释放链表内存
    while (L) {
        LNode* temp = L;
        L = L->next;
        delete temp;
    }

    return 0;
}
