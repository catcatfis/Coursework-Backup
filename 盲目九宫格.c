#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 3

// 九宫格状态结构体
typedef struct {
    int board[SIZE][SIZE];
    int x, y; // 空格的位置
} State;

// 队列节点结构体
typedef struct Node {
    State state;
    struct Node* parent;
    int move; // 0:上, 1:右, 2:下, 3:左
} Node;

// 队列结构体
typedef struct {
    Node** nodes;
    int front, rear;
    int capacity;
} Queue;

// 创建队列
Queue* createQueue(int capacity) {
    Queue* queue = (Queue*)malloc(sizeof(Queue));
    queue->nodes = (Node**)malloc(capacity * sizeof(Node*));
    queue->front = queue->rear = 0;
    queue->capacity = capacity;
    return queue;
}

// 检查队列是否为空
int isEmpty(Queue* queue) {
    return queue->front == queue->rear;
}

// 入队
void enqueue(Queue* queue, Node* node) {
    if (queue->rear == queue->capacity) {
        // 队列满，需要扩容
        queue->capacity *= 2;
        queue->nodes = (Node**)realloc(queue->nodes, queue->capacity * sizeof(Node*));
    }
    queue->nodes[queue->rear++] = node;
}

// 出队
Node* dequeue(Queue* queue) {
    if (isEmpty(queue)) {
        return NULL;
    }
    return queue->nodes[queue->front++];
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

// 广度优先搜索
Node* bfs(State start, State goal) {
    Queue* queue = createQueue(1000);
    
    // 创建初始节点
    Node* startNode = (Node*)malloc(sizeof(Node));
    startNode->state = start;
    startNode->parent = NULL;
    startNode->move = -1;
    
    enqueue(queue, startNode);
    
    while (!isEmpty(queue)) {
        Node* current = dequeue(queue);
        
        // 检查是否达到目标状态
        if (isSameState(current->state, goal)) {
            free(queue->nodes);
            free(queue);
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
                enqueue(queue, newNode);
            }
        }
    }
    
    free(queue->nodes);
    free(queue);
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
    
    printf("开始搜索解决方案...\n");
    Node* solution = bfs(start, goal);
    
    if (solution != NULL) {
        printf("找到解决方案:\n");
        printSolution(solution);
    } else {
        printf("没有找到解决方案。\n");
    }
    
    // 释放内存（简单实现中省略了完整的释放过程）
    
    return 0;
}