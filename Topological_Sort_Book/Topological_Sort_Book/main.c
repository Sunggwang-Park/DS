//
//  main.c
//  Topological_Sort_Book
//
//  Created by APPLE on 25/08/2020.
//  Copyright © 2020 DataStructure. All rights reserved.
//

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
}GraphType;

void init_graph(GraphType *g){
    g->n = 0;
    for (int i = 0; i < MAX_VERTICES; i++)
        g->adj_list[i] = NULL;
    
}

void insert_vertex(GraphType *g){
    if( g->n + 1 > MAX_VERTICES){
        fprintf(stderr, "insert_vertex 에러 : 그래프 정점의 개수 초과");
        return;
    }
    g->n++;
}

void insert_edge(GraphType *g, int u, int v){
    if( u >= g->n || v >= g->n){
        fprintf(stderr, "insert_edge 오류 - 정점 번호 오류");
        return;
    }
    GraphNode *node = (GraphNode *)malloc(sizeof(GraphNode));
    node->vertex = v;
    node->link = g->adj_list[u];
    g->adj_list[u] = node;
}

//------------------------Stack----------------------------------------

typedef struct StackNode{
    int key;
    struct StackNode *link;
}StackNode;

typedef struct StackType{
    StackNode *top;
}StackType;

void init_stack(StackType *s){
    
    s->top = NULL;
}

int is_empty(StackType *s){
    
    return s->top == NULL;
}

void push_stack(StackType *s, int value){
    
    StackNode *node = (StackNode *)malloc(sizeof(StackNode));
    node->key = value;
    node->link = s->top;
    s->top = node;
    
}

int pop_stack(StackType *s){
    if(is_empty(s)){
        fprintf(stderr, "pop_stack 에러 - 스택이 비어있음\n");
        return -1;
    }
    StackNode *node = s->top;
    int result = node->key;
    
    s->top = node->link;
    
    free(node);
    return result;
    
}
//--------------------------------Stack------------------------------


void topo_sort(GraphType *g){
    StackType s;
    GraphNode *node;
    
    //모든 정점의 진입 차수를 계산
    int *in_degree = (int *)malloc(g->n * sizeof(int));
    for (int i = 0; i < g->n; i++) //초기화
        in_degree[i] = 0;
    for (int i = 0; i < g->n; i++) {
        GraphNode *node = g->adj_list[i];   //정점 i에서 나오는 간선들
        while (node != NULL) {
            in_degree[node->vertex]++;
            node = node->link;
        }
    }
    //진입 차수가 0인 정점을 스택에 삽입
    init_stack(&s);
    for (int i = 0; i < g->n; i++) {
        if( in_degree[i] == 0) push_stack(&s, i);
    }
    
    //위상 순서를 생성
    while (!is_empty(&s)) {
        int value = pop_stack(&s);
        printf("%d ", value);
        node = g->adj_list[value];
        while(node){
            in_degree[node->vertex]--;
            if(in_degree[node->vertex] == 0)
                push_stack(&s, node->vertex);
            node = node->link;
            
        }
        
    }
    free(in_degree);
    
}

int main(int argc, const char * argv[]) {
    
    GraphType g;
    
    init_graph(&g);
    
    for(int i = 0; i < 6; i++){
        insert_vertex(&g);
    }
    
    insert_edge(&g, 0, 2);
    insert_edge(&g, 0, 3);
    
    insert_edge(&g, 1, 3);
    insert_edge(&g, 1, 4);
    
    insert_edge(&g, 2, 3);
    insert_edge(&g, 2, 5);
    
    insert_edge(&g, 3, 5);
    insert_edge(&g, 4, 5);
    
    topo_sort(&g);
    
    return 0;
}
