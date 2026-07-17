#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>  // 添加高精度时间头文件

#define MAXSIZE 20
#define CITYNUM 5
#define ArcNum (CITYNUM-1)*CITYNUM/2

typedef char CITYNAME[MAXSIZE];

typedef struct ARCTYPE {
    CITYNAME v, u;
    float distance;
} *MAPGRAPH;

typedef struct {
    CITYNAME city[CITYNUM+1];
    float globaldistance;
} TRAVELPATH;

float dist(MAPGRAPH map, CITYNAME u, CITYNAME v) {
    for (int i = 0; i < ArcNum; i++) {
        if ((strcmp(map[i].u, u) == 0 && strcmp(map[i].v, v) == 0) || 
            (strcmp(map[i].u, v) == 0 && strcmp(map[i].v, u) == 0)) {
            return map[i].distance;
        }
    }
    return -1;
}

void TraPathDis(MAPGRAPH map, TRAVELPATH *trapath) {
    float dis = 0;
    for (int i = 0; i < CITYNUM; i++) {
        float d = dist(map, trapath->city[i], trapath->city[i+1]);
        if (d < 0) {
            trapath->globaldistance = -1;
            return;
        }
        dis += d;
    }
    trapath->globaldistance = dis;
}

void CopyTraPath(TRAVELPATH *trapath, TRAVELPATH *newtrapath) {
    for (int i = 0; i < CITYNUM+1; i++) {
        strcpy(newtrapath->city[i], trapath->city[i]);
    }
    newtrapath->globaldistance = trapath->globaldistance;
}

void ExchangeCityForTraPath(TRAVELPATH *trapath, int loci, int locj) {
    CITYNAME temp;
    strcpy(temp, trapath->city[loci]);
    strcpy(trapath->city[loci], trapath->city[locj]);
    strcpy(trapath->city[locj], temp);
}

#define NEIGHBORNUM ((CITYNUM-1)*(CITYNUM-2)/2)

TRAVELPATH *ExpandTraPaths(MAPGRAPH map, TRAVELPATH *trapath) {
    TRAVELPATH *neighbors = (TRAVELPATH *)malloc(sizeof(TRAVELPATH) * NEIGHBORNUM);
    if (!neighbors) return NULL;

    int i = 0;
    for (int loci = 1; loci < CITYNUM-1; loci++) {
        for (int locj = loci+1; locj < CITYNUM; locj++) {
            CopyTraPath(trapath, &neighbors[i]);
            ExchangeCityForTraPath(&neighbors[i], loci, locj);
            TraPathDis(map, &neighbors[i]);
            i++;
        }
    }
    return neighbors;
}

void ClearAllTraPaths(TRAVELPATH *neighbors) {
    free(neighbors);
}

// 使用高精度时间作为随机种子
void InitTraPath(MAPGRAPH map, CITYNAME cities[CITYNUM], CITYNAME start, TRAVELPATH *trapath) {
    int j = 0;
    CITYNAME cs[CITYNUM-1], temp;
    
    for (int i = 0; i < CITYNUM; i++) {
        if (strcmp(cities[i], start) != 0) {
            strcpy(cs[j++], cities[i]);
        }
    }
    
    strcpy(trapath->city[0], start);
    strcpy(trapath->city[CITYNUM], start);

    // 高精度随机种子：结合微秒和纳秒
    struct timeval tv;
    gettimeofday(&tv, NULL);
    unsigned int seed = tv.tv_sec * 1000000 + tv.tv_usec;
    srand(seed);

    for (int i = 0; i < CITYNUM-1; i++) {
        int k = i + rand() % (CITYNUM-1 - i);
        strcpy(temp, cs[i]);
        strcpy(cs[i], cs[k]);
        strcpy(cs[k], temp);
    }
    
    for (int i = 1; i < CITYNUM; i++) {
        strcpy(trapath->city[i], cs[i-1]);
    }
    
    TraPathDis(map, trapath);
}

void priTraPath(TRAVELPATH path) {
    for (int i = 0; i <= CITYNUM; i++) {
        printf("%s", path.city[i]);
        if (i < CITYNUM) printf("->");
    }
    printf(" (总距离: %.2f)\n", path.globaldistance);
}

void SearchResult(MAPGRAPH map, TRAVELPATH *trapath, TRAVELPATH *trapathres) {
    TRAVELPATH *neighbors;
    int improved;
    
    CopyTraPath(trapath, trapathres);
    
    do {
        improved = 0;
        neighbors = ExpandTraPaths(map, trapathres);
        
        for (int i = 0; i < NEIGHBORNUM; i++) {
            if (neighbors[i].globaldistance > 0 && 
                (trapathres->globaldistance < 0 || 
                 neighbors[i].globaldistance < trapathres->globaldistance)) {
                CopyTraPath(&neighbors[i], trapathres);
                improved = 1;
            }
        }
        
        ClearAllTraPaths(neighbors);
    } while (improved);
}

int main() {
    TRAVELPATH trapath, trapathres;
    CITYNAME cities[CITYNUM] = {"A", "B", "C", "D", "E"};
    
    // 定义城市间距离地图
    struct ARCTYPE map_data[ArcNum] = {
        {"A", "B", 3}, {"A", "C", 2}, {"A", "D", 9}, {"A", "E", 7},
        {"B", "C", 7}, {"B", "D", 2}, {"B", "E", 5},
        {"C", "D", 9}, {"C", "E", 2},
        {"D", "E", 3}
    };
    MAPGRAPH map = map_data;

    // 运行两次算法（展示不同随机初始化的结果）
    for (int i = 0; i < 2; i++) {
        InitTraPath(map, cities, "A", &trapath);
        printf("初始路径: ");
        priTraPath(trapath);
        
        SearchResult(map, &trapath, &trapathres);
        printf("优化路径: ");
        priTraPath(trapathres);
        printf("\n");
    }
    
    return 0;
}