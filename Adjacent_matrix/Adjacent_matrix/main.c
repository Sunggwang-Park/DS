//
//  main.c
//  Adjacent_matrix
//
//  Created by APPLE on 10/07/2020.
//  Copyright © 2020 DataStructure. All rights reserved.
//

//인접 행렬을 이용한 그래프 추상 데이터 타입

#include <stdio.h>

#define MAX_VERTICES 50
typedef struct GraphType{
    int n; //정점의 개수
    int adj_mat[MAX_VERTICES][MAX_VERTICES];
}GraphType;

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

int main(int argc, const char * argv[]) {
    // insert code here...
    printf("Hello, World!\n");
    return 0;
}
