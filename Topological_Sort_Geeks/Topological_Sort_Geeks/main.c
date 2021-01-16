//
//  main.c
//  Topological_Sort_Geeks
//
//  Created by APPLE on 25/08/2020.
//  Copyright © 2020 DataStructure. All rights reserved.
//

//순환적인 위상정렬

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define MAX_VERTICES 50

//--------------------------------Stack------------------------------
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



void topo_recursive(GraphType *g, bool visited[] , StackType *s, int v){
    
    visited[v] = true;
    
    GraphNode *temp = g->adj_list[v];
    while (temp) {
        if(!visited[temp->vertex])
            topo_recursive(g, visited, s, temp->vertex);
        
        temp = temp->link;
            
    }
    
    push_stack(s, v);
    
}

void topo_sort(GraphType *g){
    StackType s;
    init_stack(&s);
    
    bool *visited = (bool *)malloc(sizeof(g->n * sizeof(bool)));
    
    for (int i = 0; i < g->n; i++) {
        visited[i] = false;
    }
    
    for (int i = 0; i < g->n; i++) {
        if(!visited[i]){
            topo_recursive(g, visited, &s, i);
        }
    }
    
    while (!is_empty(&s)) {
        StackNode *temp = s.top;
        printf("%d ",temp->key);
        pop_stack(&s);
    }
    
    
 
}


// Driver program to test above functions
int main()
{
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
