//
//  main.c
//  Depth_First_Search_matrix
//
//  Created by APPLE on 12/07/2020.
//  Copyright © 2020 DataStructure. All rights reserved.
//

//인접 행렬을 이용한 DFS(Depth First Search - 깊이 우선 탐색) 구현
//책의 코드와

#include <stdio.h>
#include <stdbool.h>


#define MAX_VERTICES 50
typedef struct GraphType{
    int n; //정점의 개수
    int adj_mat[MAX_VERTICES][MAX_VERTICES];
    int visited[MAX_VERTICES];
    int component;
}GraphType;


//그래프 초기화
void graph_init(GraphType *g)
{
    int r,c;
    g->n = 0;
    g->component = 1;
    for(r = 0; r < MAX_VERTICES; r++)
        for(c = 0; c < MAX_VERTICES; c++){
            g->adj_mat[r][c] = 0;
            g->visited[r] = 0;
        }
}

//정점 삽입 연산
void insert_vertex(GraphType *g, int v)
{
    if ( (g->n) + 1 > MAX_VERTICES) {
        fprintf(stderr, "그래프: 정점의 개수 초과");
        return;
    }
    g->n++;
}

//간선 삽입 연산
void insert_edge(GraphType *g, int start, int end)
{
    if (start >= g->n || end >= g->n) {
        fprintf(stderr, "그래프 : 정점 번호 오류");
        return;
    }
    g->adj_mat[start][end] = 1;
    g->adj_mat[end][start] = 1;
}

void dfs_mat(GraphType *g, int v)
{
    g->visited[v] = g->component;
    printf("%d ", v);
    for (int w = 0; w < g->n; w++) {
        if( g->adj_mat[v][w] && !g->visited[w]){
           // printf("%d -> %d \n", v, w);
            dfs_mat(g,w);
          //  printf("%d으로 backtracking\n",v);
        }
    }
}
void find_connected_component(GraphType *g)
{
    
    for(int i = 0; i < g->n; i++)
        if (!g->visited[i]) {
            
            dfs_mat(g,i);
            printf("\n");
            g->component++;
        }
    
    for(int i = 0; i < g->n; i++){
        printf("%d  %d\n" , i , g->visited[i] );
    }
}




int main(int argc, const char * argv[]) {
    
    GraphType g;
 
    
    graph_init(&g);
    
    
    insert_vertex(&g, 0);
    insert_vertex(&g, 1);
    insert_vertex(&g, 2);
    insert_vertex(&g, 3);
    insert_vertex(&g, 4);
    
    
    insert_edge(&g, 0, 1);
    insert_edge(&g, 0, 2);
 
    insert_edge(&g, 3, 4);
   
    
    
    find_connected_component(&g);
    
    
    
    
    return 0;
}
