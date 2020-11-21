//
//  main.c
//  Breadth_First_Search_adjacent_list
//
//  Created by APPLE on 13/07/2020.
//  Copyright © 2020 DataStructure. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_VERTICES 50




typedef int element;

typedef struct QueueNode{
    element item;
    struct QueueNode *link;
}QueueNode;

typedef struct{
    QueueNode *front, *rear;
}QueueType;

void error(char *message)
{
    fprintf(stderr, "%s\n", message);
    exit(1);
}

//초기화 함수
void init(QueueType *q)
{
    q->front = q->rear = NULL;
    
}

//공백 함수
int is_empty(QueueType *q)
{
    return q->front == NULL;
    
}

//삽입 함수
void enqueue(QueueType *q, element item)
{
    QueueNode *temp = (QueueNode *)malloc(sizeof(QueueNode));
    if (temp == NULL) {
        error("메모리 할당 오류 - 삽입할 노드의 메모리가 할당 되지 않습니다");
    }
    temp->item = item;
    temp->link = NULL;
    if(is_empty(q)){       //공백 큐일때
        q->front = temp;
        q->rear = temp;
    }
    else{                   //큐가 공백이 아니면
        q->rear->link = temp;
        q->rear = temp;
    }
}

element dequeue(QueueType *q)
{
    if(is_empty(q))
        error("삭제 함수 오류 - 큐가 공백상태입니다");
    
    QueueNode *temp = q->front;
    q->front = q->front->link;
    
    element item = temp->item;
    if (q->front==NULL) {       //공백상태
        q->rear = NULL;
    }
    free(temp);                 //노드 메모리 해제
    return item;                //데이터 반환
    
}

element peek(QueueType *q)
{
    if(is_empty(q))
        error("미리보기 오류 - 큐가 공백상태입니다");
    return q->front->item;
}


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

void bfs_list(GraphType *g, int v)
{
    GraphNode *w;
    QueueType q;
    init(&q);       //큐 초기화
    g->visited[v] = true;   //정점 v 방문 표시
    printf("%d ", v);       //정점 v 출력
    enqueue(&q, v);         //시작 정점을 큐에 저장
    while (!is_empty(&q)) {
        v = dequeue(&q);    //큐에서 정점 추출
        for (w = g->adj_list[v]; w; w = w->link)
            if(!g->visited[w->vertex]){         //미방문 정점 탐색
                g->visited[w->vertex] = true;   //방문 표시
                printf("%d ", w->vertex);       //정점 출력
                enqueue(&q, w->vertex);         //방문한 정점을 큐에 삽입
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
    insert_edge_non_direction(&g, 0, 4);
    insert_edge_non_direction(&g, 1, 2);
    insert_edge_non_direction(&g, 2, 3);
    insert_edge_non_direction(&g, 2, 4);        
    insert_edge_non_direction(&g, 3, 4);
    
    

    
    bfs_list(&g, 0);
    
    return 0;
}
