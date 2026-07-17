#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <stack>

#define EqualFun strcmp
#define SetValue strcpy
using namespace std;
#define NAMESIZE 20
typedef char NODE[NAMESIZE];
typedef int STATUS;
#define TRUE 1
#define FALSE 0

struct BROTHERNODE
{
    NODE node;
    struct BROTHERNODE *next;
};
typedef struct BROTHERNODE *BROTHER;
struct PARENTNODE
{
    NODE node;
    BROTHER children;
};
typedef struct PARENTNODE PARENT;
struct TREENODE
{
    PARENT node;
    struct TREENODE *next;
};
typedef struct TREENODE *TREE;

// 修改函数参数类型
int Equal (NODE n1, NODE n2, int (*fun)(const char*, const char*))
{
    return fun(n1, n2); // 添加返回值
}
// 修改函数参数类型
void Set(NODE n1, NODE n2, char* (*fun)(char*, const char*)){
    fun(n1, n2);
}
BROTHER AddABrother(BROTHER br , NODE node)
{
    BROTHER b, pb;
    b = (BROTHER)malloc(sizeof(struct BROTHERNODE));
    Set(b->node, node, SetValue);
    if(br == NULL)
        br = b;
    else
    {
        pb = br;
        while(pb->next) pb = pb->next;
        pb->next = b;
    }
    b->next = NULL; // 添加 next 指针初始化
    return br;
}
// 修正函数名大小写
TREE Form_Pa_Ch(NODE pa, BROTHER br)
{
    TREE parent;
    parent = (TREE)malloc(sizeof(struct TREENODE));
    Set(parent->node.node, pa, SetValue);
    // 修正拼写错误
    parent->node.children = br; 
    parent->next = NULL;
    return parent;
}
TREE AddAsubTree(TREE tree, TREE subtree){
    TREE t = tree;
    if(tree == NULL)
        tree = subtree;
    else
    {
        while(t->next)
            t = t->next;
        t->next = subtree;
    }
    return tree;
} 
BROTHER ClearBrothers(BROTHER br)
{
    BROTHER br1 = br;
    while(br)
    {
        br1 = br;
        br = br->next;
        free(br1);
    }
    return br;
}

TREE ClearTree(TREE tree)
{
    TREE tree1 = tree;
    while(tree)
    {
        tree1 = tree;
        tree = tree->next;
        free(tree1);
    }
    return tree;
}

// 修正拼写错误
void CreateStr(char *brotherset)
{
    char *c = brotherset;
    while(*c)
    {
        if(*c == '/') *c = '\0';
        c++;
    }
}

// 定义 AddBrother 函数
BROTHER AddBrother(BROTHER br, NODE node) {
    return AddABrother(br, node);
}

BROTHER CreateBrothers(BROTHER brothers, char *brotherset)
{
    char *p = brotherset;
    NODE node;
    CreateStr(brotherset);
    while(*p)
    {
        Set(node, p, SetValue);
        brothers = AddBrother(brothers, node);
        p += strlen(node) + 1;
    }
    return brothers;
}

TREE CreateTree(TREE tree, char *filename)
{
    TREE subtree;
    BROTHER brothers;
    FILE *fp;
    char parent[200], brotherset[5000];
    fp = fopen(filename, "r");
    if (fp == NULL) {
        perror("Failed to open file");
        return tree;
    }
    // 修改循环条件
    while(fscanf(fp, "%s %s", parent, brotherset) == 2)
    {
        brothers = NULL;
        brothers = CreateBrothers(brothers, brotherset);
        // 修正函数名大小写
        subtree = Form_Pa_Ch(parent, brothers);
        tree = AddAsubTree(tree, subtree);
    }
    fclose(fp);
    return tree;
}

// 修正函数定义语法错误
STATUS Search(TREE tree, NODE start, NODE end)
{
    stack<NODE> S;
    S.push(start);
    while (!S.empty()){
        NODE v;
        memcpy(v, S.top(), sizeof(NODE));
        S.pop();
        if (Equal(v, end, EqualFun) == 0) return TRUE;
        BROTHER C = ExpandNodes(tree, v);
        BROTHER p = C;
        while (p) {
            S.push(p->node);
            p = p->next;
        }
        ClearBrothers(C);
    }
    return FALSE;
}

BROTHER CopyBrothers(BROTHER children)
{
    BROTHER copynode, lastnode, head = NULL;
    while(children)
    {
        copynode = (BROTHER)malloc(sizeof(struct BROTHERNODE));
        Set(copynode->node, children->node, SetValue);
        copynode->next = NULL;
        if(head == NULL)
            head = copynode;
        else
            lastnode->next = copynode;
        lastnode = copynode;
        children = children->next;
    }
    return head;
}

// 修正 NULL 拼写错误
BROTHER ExpandNodes(TREE tree , NODE pa){
    BROTHER children = NULL;
    TREE t = tree;
    while(t)
    {
        if(Equal(t->node.node, pa, EqualFun) == 0)
        {
            children = CopyBrothers(t->node.children);
            break;
        }
        t = t->next;
    }
    return children;
}

typedef struct BROTHERNODE *STACK;
STACK PushChildren(STACK stack , BROTHER children)
{
    BROTHER p, head;
    head = CopyBrothers(children);
    p = head;
    if (p != NULL){
        while(p->next)
            p = p->next;
        p->next = stack;
        stack = head;
    }
    return stack;
}
// 移除未使用参数
STACK PopChild(STACK stack)
{
    BROTHER p, prev = NULL;
    p = stack;
    if (p != NULL) {
        while(p->next != NULL) {
            prev = p;
            p = p->next;
        }
        if (prev) {
            prev->next = NULL;
        } else {
            stack = NULL;
        }
        free(p);
    }
    return stack;
}
STACK ClearStack(STACK stack)
{
    stack = ClearBrothers((BROTHER)stack);
    return stack;
}

void main()
{
    NODE start,end;
    TREE tree;
    STATUS flag;
    char *filename = "E:\\我的文档\\树-digui.txt";
    tree = CreateTree(tree,filename);
    cout << "The Start Node:";
    cin >> start;
    cout << "The End Node:";
    cin >> end;
    flag = Search(tree, start, end);
    cout << "Search" + end + "from" + "," + "Status=" + flag + endl;
    cout << "=============================" + endl;
    ClearTree(tree);
}
