#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// 定义多叉树节点结构
typedef struct MultiTreeNode {
    int val;
    int childCount;
    struct MultiTreeNode **children; // 子节点数组
} MultiTreeNode;

// 创建新节点
MultiTreeNode* createMultiNode(int value, int numChildren) {
    MultiTreeNode* newNode = (MultiTreeNode*)malloc(sizeof(MultiTreeNode));
    newNode->val = value;
    newNode->childCount = numChildren;
    if (numChildren > 0) {
        newNode->children = (MultiTreeNode**)malloc(numChildren * sizeof(MultiTreeNode*));
    } else {
        newNode->children = NULL;
    }
    return newNode;
}

// 判断节点是否存在于多叉树中
bool isNodeInMultiTree(MultiTreeNode* root, int target) {
    if (root == NULL) {
        return false;
    }
    
    if (root->val == target) {
        return true;
    }
    
    // 递归检查所有子节点
    for (int i = 0; i < root->childCount; i++) {
        if (isNodeInMultiTree(root->children[i], target)) {
            return true;
        }
    }
    
    return false;
}

// 测试代码
int main() {
    // 构建一个示例多叉树
    //       1
    //     / | \
    //    2  3  4
    //   / \
    //  5   6
    MultiTreeNode* root = createMultiNode(1, 3);
    root->children[0] = createMultiNode(2, 2);
    root->children[1] = createMultiNode(3, 0);
    root->children[2] = createMultiNode(4, 0);
    root->children[0]->children[0] = createMultiNode(5, 0);
    root->children[0]->children[1] = createMultiNode(6, 0);
    
    // 测试节点是否存在
    int testValues[] = {1, 3, 6, 7};
    for (int i = 0; i < sizeof(testValues)/sizeof(testValues[0]); i++) {
        if (isNodeInMultiTree(root, testValues[i])) {
            printf("节点 %d 存在于树中\n", testValues[i]);
        } else {
            printf("节点 %d 不存在于树中\n", testValues[i]);
        }
    }
    
    // 释放内存（实际应用中需要更完整的内存管理）
    // ...
    
    return 0;
}