#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// 定义二叉树节点结构
typedef struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
} TreeNode;

// 创建新节点
TreeNode* createNode(int val) {
    TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
    newNode->val = val;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// 查找路径的辅助函数
bool findPathHelper(TreeNode* root, int target, int path[], int* pathIndex) {
    if (root == NULL) {
        return false;
    }
    
    // 将当前节点加入路径
    path[*pathIndex] = root->val;
    (*pathIndex)++;
    
    // 如果找到目标节点，返回true
    if (root->val == target) {
        return true;
    }
    
    // 递归查找左子树和右子树
    if (findPathHelper(root->left, target, path, pathIndex) || 
        findPathHelper(root->right, target, path, pathIndex)) {
        return true;
    }
    
    // 如果当前节点的子树中没有目标节点，则从路径中移除当前节点
    (*pathIndex)--;
    return false;
}

// 查找从根节点到目标节点的路径
void findPath(TreeNode* root, int target) {
    int path[100]; // 假设路径长度不超过100
    int pathIndex = 0;
    
    if (findPathHelper(root, target, path, &pathIndex)) {
        printf("Path found: ");
        for (int i = 0; i < pathIndex; i++) {
            printf("%d ", path[i]);
            if (i != pathIndex - 1) {
                printf("-> ");
            }
        }
        printf("\n");
    } else {
        printf("Target node not found in the tree.\n");
    }
}

int main() {
    // 构建示例二叉树
    //       1
    //      / \
    //     2   3
    //    / \   \
    //   4   5   6
    TreeNode* root = createNode(1);
    root->left = createNode(2);
    root->right = createNode(3);
    root->left->left = createNode(4);
    root->left->right = createNode(5);
    root->right->right = createNode(6);
    
    // 查找路径
    printf("Path to 4: ");
    findPath(root, 4);
    
    printf("Path to 6: ");
    findPath(root, 6);
    
    printf("Path to 7: ");
    findPath(root, 7);
    
    return 0;
}