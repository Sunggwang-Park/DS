//
//  main.c
//  Depth_First_Search_adjacent_list
//
//  Created by APPLE on 12/07/2020.
//  Copyright © 2020 DataStructure. All rights reserved.
//

//인접 리스트로 구현한 DFS(Depth First Search - 깊이 우선 탐색)

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_VERTICES 50

typedef struct GraphNode{
    int vertex;
    struct GraphNode *link;
}GraphNode;

typedef struct GraphType{
    int n;  //정점의 개수
    GraphNode *adj_list[MAX_VERTICES];
    bool visited[MAX_VERTICES];
}GraphType;

void graph_init(GraphType *g)
{
    int v;
    g->n = 0;
    for(v = 0; v < MAX_VERTICES; v++){
        g->adj_list[v] = NULL;
        g->visited[v] = 0;
    }
    
}

void insert_vertex(GraphType *g, int v)
{
    if ((g->n) + 1 > MAX_VERTICES) {
        fprintf(stderr, "그래프: 정점의 개수 초과");
        return;
    }
    g->n++;
}


//간선 삽입 연산, v를 u의 인접 리스트에 삽입한다
void insert_edge_non_direction(GraphType *g, int u, int v)
{
    GraphNode *node;
    if (u >= g->n || v >= g->n) {
        fprintf(stderr, "그래프: 정점 번호 오류");
        return;
    }
    node = (GraphNode *)malloc(sizeof(GraphNode));
    node->vertex = v;
    node->link = g->adj_list[u];
    g->adj_list[u] = node;
    
    node = (GraphNode *)malloc(sizeof(GraphNode));
    node->vertex = u;
    node->link = g->adj_list[v];
    g->adj_list[v] = node;
}

//연결 리스트로 표현된 그래프에 대한 깊이 우선 탐색
void dfs_list(GraphType *g, int v)
{
    GraphNode *w;
    printf("%d ", v);
    g->visited[v] = 1;
    for (w = g->adj_list[v]; w; w = w->link) {
        if(!g->visited[w->vertex]){
            printf("%d -> %d\n", v, w->vertex);
            dfs_list(g, w->vertex);
//            printf("%d으로 backtracking\n", v);
        }
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
    
    insert_edge_non_direction(&g, 0, 1);
   
    
    insert_edge_non_direction(&g, 0, 2);

    
    insert_edge_non_direction(&g, 1, 2);
   
    
    insert_edge_non_direction(&g, 2, 3);
   
    
    insert_edge_non_direction(&g, 2, 4);
   
    
    insert_edge_non_direction(&g, 3, 4);
    
    
    insert_edge_non_direction(&g, 4, 0);
    
    
    dfs_list(&g, 0);
    
    return 0;
}
