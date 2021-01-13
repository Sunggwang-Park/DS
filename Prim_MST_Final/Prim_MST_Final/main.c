//
//  main.c
//  Prim_MST_Final
//
//  Created by APPLE on 19/08/2020.
//  Copyright © 2020 DataStructure. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>

#define INF INT_MAX
#define VERTICES 7

typedef struct subset{
    int dist[VERTICES];
    int parent[VERTICES];
    bool selected[VERTICES];
}subset;

void init_subset(subset *s){
    for (int i = 0; i < VERTICES; i++) {
        s->dist[i] = INF;
        s->selected[i] = false;
    }
}

//dist 배열 중 선택되지 않았고 가장 작은 dist의 인덱스를 반환
int min_key(subset *s){
    int min = INF, min_index = 0;
    
    for(int i = 0; i < VERTICES; i++){
        if(!s->selected[i] && s->dist[i] < min){
            min = s->dist[i];
            min_index = i;
        }
    }
    
    return min_index;
}

void prim(int g[][VERTICES]){
    int min;
    subset mst;
    init_subset(&mst);
    
    mst.dist[0] = 0;
    mst.parent[0] = -1;
    
    for(int i = 0; i < VERTICES -1; i++){
        min = min_key(&mst);
        mst.selected[min] = true;
        
        for(int n = 0; n < VERTICES; n++){
            if(!mst.selected[n] && g[min][n] != INF && g[min][n] < mst.dist[n]){
                mst.dist[n] = g[min][n];
                mst.parent[n] = min;
            }
        }
    }
    
    for (int i = 1; i < VERTICES; i++) {
        printf("%d %d - %d\n", mst.parent[i], i, g[i][mst.parent[i]]);
         //g[i][s->parent[i]]  -->  mst.dist[i] 로 표현 가능 (값 동일)
    }
    
}

int main(){
    int Graph[VERTICES][VERTICES] ={
        { 0, 29, INF, INF, INF, 10, INF },
        { 29, 0, 16, INF, INF, INF, 15 },
        { INF, 16, 0, 12, INF, INF, INF },
        { INF, INF, 12, 0, 22, INF, 18 },
        { INF, INF, INF, 22, 0, 27, 25 },
        { 10, INF, INF, INF, 27, 0, INF },
        { INF, 15, INF, 18, 25, INF, 0}
    };
    
    prim(Graph);
    
    return 0;
}
