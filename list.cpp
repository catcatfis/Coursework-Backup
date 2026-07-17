
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
Status GetElem(LinkList L, int i, ElemType& e) {
   p=L->next;
   int j=1;
   while(p&&j<i){
    p=p->next;
    ++j; 
   } 
   if(!p||j>i)return ERROR;
   e=p->data;
   return OK;
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
void CreateList_H(LinkList& L, int n) {
    L = new LNode;
    L->next = NULL;
    for (int i = n; i > 0; --i) {
        p = new LNode;
        cin >> p->data;
        p->next = L->next;
        L->next = p;
    } 
}
void DuLinkList (LinkList& L) {
    p = L->next;
    while (p) {
        q = new LNode;
        q->data = p->data;
        q->next = p->next;
        p->next = q;
        p = q->next;
    } 
}
Status GetElemP_DuL(int DuLinkList(LinkList& L), int i, DuLNode*& p) {
        p=L->next;
        int j=1;
        while(p&&j<i){
            p=p->next;
            ++j;
        }
        if(!p||j>i)return ERROR;
        return OK;
    }
void CreateList_R(LinkList& L, int n) {
    L = new LNode;
    L->next = NULL;
    r = L; 
    for (int i = 0; i < n; ++i) {
        p = new LNode;
        cin >> p->data;
        p->next = NULL;
        r->next = p;
        r = p; 
    }
}
typedef struct DuLNode {
    ElemType data;
    struct DuLNode* prior;
    struct DuLNode* next; 
}DuLNode, * DuLinkList;
Status LisqtInsert_DuL(DuLinkList& L, int i, ElemType e) {
  if(!(p=GetElemP_DuL(L,i)))return ERROR;
  s=new DuLNode;
  s->data=e;
  s->prior=p->prior;
  p->prior->next=s;
  s->next=p;
  p->prior=s;
  return OK; 
}
Status ListDelete_DuL(DuLinkList& L, int i, ElemType& e) {
    if(!(p=GetElemP_DuL(L,i)))return ERROR;
    e=p->data;
    p->prior->next=p->next;
    p->next->prior=p->prior;
    delete p;
    return OK; 
}
void MergeList(List& LA, List& LB) {
    m=ListLength(LA);
    n=ListLength(LB);
    for(int i=1;i<=n;i++){
        GetElem(LB,i,e);
        if(!LocateElem(LA,e,eq)){
            ListInsert(LA,++m,e);
        } 
    }
}
void MergeList_Sq(SqList LA, SqList LB, SqList& LC) {
    LC.length=LA.length+LB.length;
    LC.elem=new ElemType[LC.length];
    pc=LC.elem;
    pa=LA.elem;
    pb=LB.elem;
    pa_last=LA.elem+LA.length-1;
    pb_last=LB.elem+LB.length-1;
    while(pa<=pa_last&&pb<=pb_last){
        if(*pa<=*pb){
            *pc++=*pa++;
        }else{
            *pc++=*pb++;
         } 
    } 
    while(pa<=pa_last)*pc++=*pa++;
    while(pb<=pb_last)*pc++=*pb++;
}
void MergeList_L(LinkList& LA, LinkList& LB, LinkList& LC){
    pa=LA->next;
    pb=LB->next;
    LC=LA;
    pc=LC;
    while(pa&&pb){
        if(pa->data<=pb->data){
            pc->next=pa;
            pc=pa;
            pa=pa->next;
        }else{
            pc->next=pb;
            pc=pb;
            pb=pb->next;
         } 
    } 
    pc->next=pa?pa:pb;
    delete LB;
}
   
    Status InitList(LinkList& L) {
        L = new LNode;
        L->next = NULL;
        return OK; 
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
    Status ListInsert(LinkList& L, int i, ElemType e) {
        p=L;
        j=0;
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
        j=0;
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
    void CreateList_H(LinkList& L, int n) {
        L = new LNode;
        L->next = NULL;
        for (int i = n; i > 0; --i) {
            p = new LNode;
            cin >> p->data;
            p->next = L->next;
            L->next = p;
        } 
    }
    void CreateList_R(LinkList& L, int n) {
        L = new LNode;
        L->next = NULL;
        r = L; 
        for (int i = 0; i < n; ++i) {
            p = new LNode;
            cin >> p->data;
            p->next = NULL;
            r->next = p;
            r = p; 
        }
    }
    typedef struct DuLNode {
        ElemType data;
        struct DuLNode* prior;
        struct DuLNode* next; 
    }DuLNode, * DuLinkList;
    Status LisqtInsert_DuL(DuLinkList& L, int i, ElemType e) {
      if(!(p=GetElemP_DuL(L,i)))return ERROR;
      s=new DuLNode;
      s->data=e;
      s->prior=p->prior;
      p->prior->next=s;
      s->next=p;
      p->prior=s;
      return OK; 
    }
    Status ListDelete_DuL(DuLinkList& L, int i, ElemType& e) {
        if(!(p=GetElemP_DuL(L,i)))return ERROR;
        e=p->data;
        p->prior->next=p->next;
        p->next->prior=p->prior;
        delete p;
        return OK; 
    }
    void MergeList(List& LA, List& LB) {
        m=ListLength(LA);
        n=ListLength(LB);
        for(int i=1;i<=n;i++){
            GetElem(LB,i,e);
            if(!LocateElem(LA,e,eq)){
                ListInsert(LA,++m,e);
            } 
        }
    }
    
    void MergeList_Sq(SqList LA, SqList LB, SqList& LC) {
        LC.length=LA.length+LB.length;
        LC.elem=new ElemType[LC.length];
        pc=LC.elem;
        pa=LA.elem;
        pb=LB.elem;
        pa_last=LA.elem+LA.length-1;
        pb_last=LB.elem+LB.length-1;
        while(pa<=pa_last&&pb<=pb_last){
            if(*pa<=*pb){
                *pc++=*pa++;
            }else{
                *pc++=*pb++;
             } 
        } 
        while(pa<=pa_last)*pc++=*pa++;
        while(pb<=pb_last)*pc++=*pb++;
    }
    void MergeList_L(LinkList& LA, LinkList& LB, LinkList& LC){
        pa=LA->next;
        pb=LB->next;
        LC=LA;
        pc=LC;
        while(pa&&pb){
            if(pa->data<=pb->data){
                pc->next=pa;
                pc=pa;
                pa=pa->next;
            }else{
                pc->next=pb;
                pc=pb;
                pb=pb->next;
             } 
        } 
        pc->next=pa?pa:pb;
        delete LB;
    }
    void display(LinkList L) {
        p=L->next;
        while(p){
            cout<<p->data<<" ";
            p=p->next;
        } 
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