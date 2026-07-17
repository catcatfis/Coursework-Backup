#include <stdio.h>
#include <stdlib.h>

typedef struct LNode {
    int data;
    struct LNode *next;
} LNode, *LinkList;
// 头插法初始化
void CreateListF(LinkList *L, int a[], int n) {
    *L = (LinkList)malloc(sizeof(LNode));
    (*L)->next = NULL;
    for (int i = n-1; i >-1; i--) {
        LNode *s = (LNode *)malloc(sizeof(LNode));
        s->data = a[i];
        s->next = (*L)->next;
        (*L)->next = s;
    }
}
// （2）尾插法初始化
void CreateListR(LinkList *L, int a[], int n) {
    *L = (LinkList)malloc(sizeof(LNode));
    (*L)->next = NULL;
    LNode *r = *L;
    for (int i = 0; i < n; i++) {
        LNode *s = (LNode *)malloc(sizeof(LNode));
        s->data = a[i];
        s->next = NULL;
        r->next = s;
        r = s;
    }
}
// （3）顺序打印各结点值
void DispList(LinkList L) {
    LNode *p = L->next;
    while (p) {
        printf("%d ", p->data);
        p = p->next;
    }
    printf("\n");
}
// （5）返回第 i 个元素的值
int GetElem(LinkList L, int i) {
    int j = 1;
    LNode *p = L->next;
    while (p && j < i) {
        p = p->next;
        j++;
    }
    if (!p || j > i) {
        return -1; // 未找到
    }
    return p->data;
}
// （6）返回 L 中第 1 个值域与 e 相等的逻辑位序。若不存在，则返回值为 0
int LocateElem(LinkList L, int e) {
    int i = 1;
    LNode *p = L->next;
    while (p && p->data != e) {
        p = p->next;
        i++;
    }
    if (p) {
        return i;
    }
    return 0;
}
// （7）在第 i 个元素位置插入元素 e，L 长度增 1
int ListInsert(LinkList *L, int i, int e) {
    int j = 0;
    LNode *p = *L;
    while (p && j < i - 1) {
        p = p->next;
        j++;
    }
    if (!p || j > i - 1) {
        return 0;
    }
    LNode *s = (LNode *)malloc(sizeof(LNode));
    s->data = e;
    s->next = p->next;
    p->next = s;
    return 1;
}

// （8）删除 L 的第 i 个元素，L 长度减 1
int ListDelete(LinkList *L, int i) {
    int j = 0;
    LNode *p = *L;
    while (p->next && j < i - 1) {
        p = p->next;
        j++;
    }
    if (!(p->next) || j > i - 1) {
        return 0;
    }
    LNode *q = p->next;
    p->next = q->next;
    free(q);
    return 1;
}
// （9）返回按元素值升序的表 L
void Sort(LinkList *L) {
    if (!(*L)->next || !(*L)->next->next) return;
    LNode *p = (*L)->next->next;
    (*L)->next->next = NULL;
    while (p) {
        LNode *q = p->next;
        LNode *pre = *L;
        while (pre->next && pre->next->data < p->data) {
            pre = pre->next;
        }
        p->next = pre->next;
        pre->next = p;
        p = q;
    }
}

int gradessort ( LinkList *L){
    
    return 0;
}
int main() {
    int a[] = {88, 77, 60, 90, 77, 24, 42};
    int n = sizeof(a) / sizeof(a[0]);
    LinkList L;
    // 头插法
    CreateListF(&L, a, n);
    printf("头插法创建的链表: ");
    DispList(L);
    // 释放头插法创建的链表内存
    while (L) {
        LNode *temp = L;
        L = L->next;
        free(temp);
    }
    // 尾插法
    CreateListR(&L, a, n);
    printf("尾插法创建的链表: ");
    DispList(L);
    printf("输入查询第几个元素\n");
    int x;
    scanf("%d",&x);
    // 获取元素
    printf("第 %d 个元素的值: %d\n",x, GetElem(L, x));
    // 查找输入值的逻辑位序
    printf("输入查找元素的值\n");
    int y;
    scanf("%d",&y);
    printf("值为 %d 的元素的逻辑位序: %d\n", y,LocateElem(L, 77));
    printf("输入插入元素的位置和值\n");
    int z,w;
    scanf("%d%d",&z,&w);
    // 在第 z个位置插入元素 w
    ListInsert(&L, z, w);
    printf("插入后的链表: ");
    DispList(L);
    // 删除元素
    printf("输入删除元素的位置\n");
    int q;
    scanf("%d",&q);
    ListDelete(&L, q);
    printf("删除后的链表: ");
    DispList(L);
    // 对链表排序
    Sort(&L);
    printf("排序后的链表: ");
    DispList(L);
    // 释放尾插法创建的链表内存
    while (L) {
        LNode *temp = L;
        L = L->next;
        free(temp);
    }

    return 0;
}