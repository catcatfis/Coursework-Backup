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
typedef struct LNode {
    ElemType data;
    struct LNode* next;
}LNode, * LinkList;
struct LNode *p;
struct LNode *s;
struct LNode *q;
struct LNode *r;
Status InitList(LinkList& L) {
    L = new LNode;
    L->next = NULL;
    return OK; 
}
void display(LinkList L) {
    p=L->next;
    while(p){
        cout<<p->data<<" ";
        p=p->next;
    } 
}
Status ListEmpty(LinkList L) {
    if (L->next) {
        cout << "非空" << endl; 
    } 
    else {
        cout << "空" << endl; 
    }
}
Status ListLength(LinkList L) {
    int i = 0;
    p = L->next;
    while (p) {
        i++;
        p = p->next;
    }
    cout << i << endl; 
}
Status GetElem(LinkList L, int i, ElemType& e) {
    p=L->next;
    j=1;
    while(p&&j<i){
     p=p->next;
     ++j; 
    } 
    if(!p||j>i)return ERROR;
    e=p->data;
    return OK;
 }
Status LocateElem(LinkList L, ElemType e, Status(*eq)(ElemType, ElemType)) {
    p=L->next;
    j=1;
    while(p&&!eq(p->data,e)){
        p=p->next;
        ++j;
    }
    if(p)return j;
    else return ERROR; 
}
Status ListInsert(LinkList& L, int i, ElemType e) {
    p=L;
    int j=0;
    while(p&&j<i-1){
        p=p->next;
        ++j;
    } 
    if(!p||j>i-1)return ERROR;
    s=new LNode;
    s->data=e;
    s->next=p->next;
    p->next=s;
    return OK;
}
Status ListDelete(LinkList& L, int i, ElemType& e) {
    p=L;
    int j=0;
    while(p->next&&j<i-1){
        p=p->next;
        ++j;
    }
    if(!p->next||j>i-1)return ERROR;
    q=p->next;
    p->next=q->next;
    e=q->data;
    delete q;
    return OK; 
}
int main() {
    while(1){
    cout<<"1初始化 2打印 3 判空 4 求长度 5 按序号查找 6 按值查找 7 插入 8 删除 "<<endl;
    cout<<"请选择功能序号："<<endl;
    int n;
    cin>>n;
    switch (n)
    {
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
        GetElem(L,i,e);
        break;
    case 6:
        LocateElem(L,e,eq);
        break;
    case 7:
        ListInsert(L,i,e);
        break;
    case 8:
        ListDelete(L,i,e);
        break;
    }
    cout<<"是否继续其他操作：Y（1）N（0）"<<endl;
    cin>>n;
    if(n==0)break;
}
}