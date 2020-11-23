//
//  main.c
//  Breadth_First_Search_adjacent_matrix
//
//  Created by APPLE on 13/07/2020.
//  Copyright © 2020 DataStructure. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_VERTICES 50
typedef struct GraphType{
    int n; //정점의 개수
    int adj_mat[MAX_VERTICES][MAX_VERTICES];
    bool visited[MAX_VERTICES];
    
}GraphType;


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

//이런 식으로 구현하면 한정된 개수의 정점까지만 그래프에 삽입할 수 있다.
//만약 동적 배열로 구현한다면 사용자가 정점을 삽입할 때마다 다시 크기를 조정할 수 있을 것이다.
//(이 문제는 연습문제에서 다루어보기로 하자) by book

//그래프 초기화
void graph_init(GraphType *g)
{
    int r,c;
    g->n = 0;
    for(r = 0; r < MAX_VERTICES; r++)
        for(c = 0; c < MAX_VERTICES; c++)
            g->adj_mat[r][c] = 0;
    
    for (int i = 0; i < MAX_VERTICES; i++) {
        g->visited[i] = 0;
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

void bfs_mat(GraphType *g, int v)
{
    
    QueueType q;
    init(&q);
    g->visited[v] = true;       //정점 v 방문 표시
    printf("%d ", v);           //정점 출력
    enqueue(&q, v);             //시작 정점을 큐에 저장
    while (!is_empty(&q)) {
        v = dequeue(&q);        //큐에서 정점 추출
        for (int w = 0; w < g->n; w++)     //인접 정점 탐색
            if (g->adj_mat[v][w] && !g->visited[w]) {
                g->visited[w] = true;   //방문 표시
                printf("%d ", w);       //정점 출력
                enqueue(&q, w);         //방문한 정점을 큐에 저장
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
    
    
    insert_edge(&g, 0, 1);
    insert_edge(&g, 0, 2);
    insert_edge(&g, 1, 2);
    insert_edge(&g, 2, 3);
    insert_edge(&g, 2, 4);
    insert_edge(&g, 3, 4);
    insert_edge(&g, 4, 0);
    
    bfs_mat(&g, 0);
    
    return 0;
}
