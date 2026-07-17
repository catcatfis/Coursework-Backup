#include <stdio.h>
#include <stdlib.h>
typedef struct LNode {
    int data;
    struct LNode *next;
} LNode, *LinkList;

void CreateListF(LinkList *L, int a[], int n) {
    *L = (LinkList)malloc(sizeof(LNode));
    (*L)->next = NULL;
    for (int i = n - 1; i >= 0; i--) {
        LNode *s = (LNode *)malloc(sizeof(LNode));
        s->data = a[i];
        s->next = (*L)->next;
        (*L)->next = s;
    }
}

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

void DispList(LinkList L) {
    LNode *p = L->next;
    while (p) {
        printf("%d ", p->data);
        p = p->next;
    }
    printf("\n");
}

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

int main() {
    int a[] = {88, 77, 60, 90, 77, 24, 42};
    int n = sizeof(a) / sizeof(a[0]);
    LinkList L;
    CreateListF(&L, a, n);
    printf("头插法创建的链表: ");
    DispList(L);

    while (L) {
        LNode *temp = L;
        L = L->next;
        free(temp);
    }

    CreateListR(&L, a, n);
    printf("尾插法创建的链表: ");
    DispList(L);
    int x;
    printf("请输入第几个元素: ");
    scanf("%d", &x);
    printf("第 %d 个元素的值: %d\n",x, GetElem(L, x));
    int y;
    printf("请输入要查找的值: ");
    scanf("%d", &y);
    printf("值为 %d 的元素的逻辑位序: %d\n", y,LocateElem(L, y));
    int z;
    int w;
    printf("请输入要插入的位置和值: ");
    scanf("%d %d", &z, &w);
    if (ListInsert(&L,z , w)) {
        printf("在第 %d 个位置插入 %d后的链表: ", z, w);
        DispList(L);
    }
    int v;
    printf("请输入要删除的位置: ");
    scanf("%d", &v);
    if (ListDelete(&L, v)) {
        printf("删除第 %d 个元素后的链表: ", v);
        DispList(L);
    }

    Sort(&L);
    printf("排序后的链表: ");
    DispList(L);

    while (L) {
        LNode *temp = L;
        L = L->next;
        free(temp);
    }

    return 0;
}