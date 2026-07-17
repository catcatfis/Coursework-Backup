#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define SIZE 3

// 九宫格状态结构体
typedef struct {
    int board[SIZE][SIZE];
    int x, y; // 空格的位置
} State;

// 优先队列节点结构体
typedef struct Node {
    State state;
    struct Node* parent;
    int move; // 0:上, 1:右, 2:下, 3:左
    int g;    // 从起始节点到当前节点的实际代价
    int h;    // 启发式函数值
    int f;    // f = g + h
} Node;

// 优先队列结构体
typedef struct {
    Node** nodes;
    int size;
    int capacity;
} PriorityQueue;

// 创建优先队列
PriorityQueue* createPriorityQueue(int capacity) {
    PriorityQueue* pq = (PriorityQueue*)malloc(sizeof(PriorityQueue));
    pq->nodes = (Node**)malloc(capacity * sizeof(Node*));
    pq->size = 0;
    pq->capacity = capacity;
    return pq;
}

// 交换两个节点
void swap(Node** a, Node** b) {
    Node* temp = *a;
    *a = *b;
    *b = temp;
}

// 上浮操作（用于插入）
void heapifyUp(PriorityQueue* pq, int index) {
    while (index > 0 && pq->nodes[(index-1)/2]->f > pq->nodes[index]->f) {
        swap(&pq->nodes[(index-1)/2], &pq->nodes[index]);
        index = (index-1)/2;
    }
}

// 下沉操作（用于删除）
void heapifyDown(PriorityQueue* pq, int index) {
    int smallest = index;
    int left = 2*index + 1;
    int right = 2*index + 2;

    if (left < pq->size && pq->nodes[left]->f < pq->nodes[smallest]->f) {
        smallest = left;
    }

    if (right < pq->size && pq->nodes[right]->f < pq->nodes[smallest]->f) {
        smallest = right;
    }

    if (smallest != index) {
        swap(&pq->nodes[index], &pq->nodes[smallest]);
        heapifyDown(pq, smallest);
    }
}

// 插入节点到优先队列
void enqueue(PriorityQueue* pq, Node* node) {
    if (pq->size == pq->capacity) {
        // 队列满，需要扩容
        pq->capacity *= 2;
        pq->nodes = (Node**)realloc(pq->nodes, pq->capacity * sizeof(Node*));
    }
    pq->nodes[pq->size] = node;
    heapifyUp(pq, pq->size);
    pq->size++;
}

// 从优先队列中取出最小f值的节点
Node* dequeue(PriorityQueue* pq) {
    if (pq->size == 0) {
        return NULL;
    }
    Node* minNode = pq->nodes[0];
    pq->nodes[0] = pq->nodes[pq->size-1];
    pq->size--;
    heapifyDown(pq, 0);
    return minNode;
}

// 检查两个状态是否相同
int isSameState(State a, State b) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (a.board[i][j] != b.board[i][j]) {
                return 0;
            }
        }
    }
    return 1;
}

// 复制状态
State copyState(State state) {
    State newState;
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            newState.board[i][j] = state.board[i][j];
        }
    }
    newState.x = state.x;
    newState.y = state.y;
    return newState;
}

// 计算曼哈顿距离启发式函数
int manhattanDistance(State state, State goal) {
    int distance = 0;
    int positions[SIZE*SIZE][2]; // 存储目标状态中每个数字的位置
    
    // 记录目标状态中每个数字的位置
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (goal.board[i][j] != 0) {
                positions[goal.board[i][j]][0] = i;
                positions[goal.board[i][j]][1] = j;
            }
        }
    }
    
    // 计算当前状态与目标状态的曼哈顿距离
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            int value = state.board[i][j];
            if (value != 0) {
                int targetX = positions[value][0];
                int targetY = positions[value][1];
                distance += abs(i - targetX) + abs(j - targetY);
            }
        }
    }
    
    return distance;
}

// 移动空格
State moveSpace(State state, int direction) {
    int x = state.x;
    int y = state.y;
    
    State newState = copyState(state);
    
    // 上
    if (direction == 0 && x > 0) {
        newState.board[x][y] = newState.board[x-1][y];
        newState.board[x-1][y] = 0;
        newState.x = x-1;
    }
    // 右
    else if (direction == 1 && y < SIZE-1) {
        newState.board[x][y] = newState.board[x][y+1];
        newState.board[x][y+1] = 0;
        newState.y = y+1;
    }
    // 下
    else if (direction == 2 && x < SIZE-1) {
        newState.board[x][y] = newState.board[x+1][y];
        newState.board[x+1][y] = 0;
        newState.x = x+1;
    }
    // 左
    else if (direction == 3 && y > 0) {
        newState.board[x][y] = newState.board[x][y-1];
        newState.board[x][y-1] = 0;
        newState.y = y-1;
    }
    
    return newState;
}

// 检查状态是否已经访问过
int isVisited(Node* node, State state) {
    while (node != NULL) {
        if (isSameState(node->state, state)) {
            return 1;
        }
        node = node->parent;
    }
    return 0;
}

// 打印状态
void printState(State state) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (state.board[i][j] == 0) {
                printf("  "); // 空格用两个空格表示
            } else {
                printf("%d ", state.board[i][j]);
            }
        }
        printf("\n");
    }
    printf("\n");
}

// 打印解决方案
void printSolution(Node* node) {
    if (node == NULL) {
        return;
    }
    printSolution(node->parent);
    printf("Move: ");
    switch(node->move) {
        case 0: printf("上\n"); break;
        case 1: printf("右\n"); break;
        case 2: printf("下\n"); break;
        case 3: printf("左\n"); break;
        default: printf("初始状态\n"); break;
    }
    printState(node->state);
}

// A*算法
Node* astar(State start, State goal) {
    PriorityQueue* openList = createPriorityQueue(1000);
    
    // 创建初始节点
    Node* startNode = (Node*)malloc(sizeof(Node));
    startNode->state = start;
    startNode->parent = NULL;
    startNode->move = -1;
    startNode->g = 0;
    startNode->h = manhattanDistance(start, goal);
    startNode->f = startNode->g + startNode->h;
    
    enqueue(openList, startNode);
    
    while (openList->size > 0) {
        Node* current = dequeue(openList);
        
        // 检查是否达到目标状态
        if (isSameState(current->state, goal)) {
            free(openList->nodes);
            free(openList);
            return current;
        }
        
        // 尝试四个方向的移动
        for (int i = 0; i < 4; i++) {
            State newState = moveSpace(current->state, i);
            
            // 检查移动是否有效且未访问过
            if (!isSameState(newState, current->state) && !isVisited(current, newState)) {
                Node* newNode = (Node*)malloc(sizeof(Node));
                newNode->state = newState;
                newNode->parent = current;
                newNode->move = i;
                newNode->g = current->g + 1;
                newNode->h = manhattanDistance(newState, goal);
                newNode->f = newNode->g + newNode->h;
                enqueue(openList, newNode);
            }
        }
    }
    
    free(openList->nodes);
    free(openList);
    return NULL; // 没有找到解决方案
}

int main() {
    // 初始状态（0代表空格）
    State start = {
        .board = {
            {2, 8, 3},
            {1, 6, 4},
            {7, 0, 5}
        },
        .x = 2,
        .y = 1
    };
    
    // 目标状态
    State goal = {
        .board = {
            {1, 2, 3},
            {8, 0, 4},
            {7, 6, 5}
        },
        .x = 1,
        .y = 1
    };
    
    printf("初始状态:\n");
    printState(start);
    
    printf("目标状态:\n");
    printState(goal);
    
    printf("开始A*搜索解决方案...\n");
    Node* solution = astar(start, goal);
    
    if (solution != NULL) {
        printf("找到解决方案(共%d步):\n", solution->g);
        printSolution(solution);
    } else {
        printf("没有找到解决方案。\n");
    }
    
    // 释放内存（简单实现中省略了完整的释放过程）
    
    return 0;
}