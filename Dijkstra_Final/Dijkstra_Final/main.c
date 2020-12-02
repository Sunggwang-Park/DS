//
//  main.c
//  Dijkstra_Final
//
//  Created by APPLE on 21/08/2020.
//  Copyright © 2020 DataStructure. All rights reserved.
//

//인접행렬을 이용한 다익스트라의 시간복잡도는 O(n^2)
//우선순위큐(힙)을 이용한 다익스트라의 시간복잡도는 O(E logV)

#include <stdio.h>
#include <limits.h>
#include <stdbool.h>

#define MAX_VERTICES 7
#define INF 1000

int min_dist(int distance[], bool found[]){
    int min = INT_MAX, min_index = -1; // 왜 -1 ?? -> -1 나오면 오류
    
    for(int i = 0; i < MAX_VERTICES; i++){
        if(!found[i] && distance[i] < min){
            min = distance[i];
            min_index = i;
        }
    }
    
    return min_index;
}

void dijkstra(int weight[][MAX_VERTICES], int start){
    int distance[MAX_VERTICES];
    int preVertex[MAX_VERTICES];
    bool found[MAX_VERTICES];
    
    for (int i =0; i < MAX_VERTICES; i++) {
        distance[i] = weight[start][i];
        preVertex[i] = start;
        found[i] = false;
    }
    
    found[start] = true;
    preVertex[start] = -1;
    
    //시작 정점은 이미 방문되었고 나머지 6개의 정점이 남았으니 0부터 n-2까지 반복한다(6번 반복)
    for(int i = 0; i < MAX_VERTICES -1; i++){
        int min = min_dist(distance, found);
        found[min] = true;
        
        for(int n = 0; n < MAX_VERTICES; n++){
            if(!found[n] && distance[min] + weight[min][n] < distance[n]){
                distance[n] = distance[min] + weight[min][n];
                preVertex[n] = min;
            }
        }
        
        
    }
    
    printf("정점 %d에서\n", start);
    for (int i = 0; i < MAX_VERTICES; i++) {
        printf("정점 %d까지의 최소 거리 : %d\n", i ,distance[i]);
    }
    
    for (int i = 0; i < MAX_VERTICES; i++) {
        printf("%d 정점의 preVertex : %d\n",i, preVertex[i]);
    }
    
    
}

int main(int argc, const char * argv[]) {
    int weight[MAX_VERTICES][MAX_VERTICES] = {  //네트워크의 인접 행렬
        { 0, 7, INF, INF,   3,  10, INF },
        { 7, 0,   4,  10,   2,   6, INF },
        {INF, 4,  0,   2, INF, INF, INF },
        {INF, 10, 2,   0,  11,  9,    4 },
        {  3,  2, INF, 11,  0,  INF,  5 },
        { 10,  6, INF, 9,  INF,  0,  INF },
        { INF, INF, INF,  4,  5, INF, 0  }
    };
    
    dijkstra(weight, 0);
    return 0;
}
