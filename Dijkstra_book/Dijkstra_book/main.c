//
//  main.c
//  Dijkstra_book
//
//  Created by APPLE on 15/07/2020.
//  Copyright © 2020 DataStructure. All rights reserved.
//
//

//책에 있는 다익스트라 알고리즘

//bad : 전역변수를 사용하였다

#include <stdio.h>
#include <stdbool.h>

#define INT_MAX 2147483647  //최대 정수
#define MAX_VERTICES 7      //정점의 수
#define INF 1000            //무한대(연결이 없는 경우)

int weight[MAX_VERTICES][MAX_VERTICES] = {  //네트워크의 인접 행렬
    { 0, 7, INF, INF,   3,  10, INF },
    { 7, 0,   4,  10,   2,   6, INF },
    {INF, 4,  0,   2, INF, INF, INF },
    {INF, 10, 2,   0,  11,  9,    4 },
    {  3,  2, INF, 11,  0,  INF,  5 },
    { 10,  6, INF, 9,  INF,  0,  INF },
    { INF, INF, INF,  4,  5, INF, 0  }
};

int distance[MAX_VERTICES];     //시작 정점으로부터의 최단 경로 거리
int found[MAX_VERTICES];        //방문한 정점 표시

int choose(int distance[], int n, int found[])  //distance 배열안에서 선택안된 정점 중 최솟값의 인덱스를 반환하는 함수
{
    int min = INT_MAX, minpos = -1;
    for (int i = 0; i < n; i++)
        if(distance[i] < min && !found[i]){
            min = distance[i];
            minpos = i;
        }
    
    return minpos;
    
}

void shortest_path(int start, int n)
{
    int u;  //최솟값의 인덱스
    for (int i = 0; i < n; i++) {   //초기화
        distance[i] = weight[start][i];     //i항의 열들을 차례대로 distance값에 대입한다
        found[i] = false;                   //아직 발견된 정점이 없으므로 모두 false로 둔다
    }
    found[start] = true;            //시작 정점 방문 표시
    distance[start] = 0;            //왜 필요하지..?
    for (int i = 0; i < n-1; i++) { //시작 정점은 이미 방문되었고 나머지 6개의 정점이 남았으니 0부터 n-2까지 반복한다(6번 반복)
        u = choose(distance, n, found); //아직 방문되지 않은 정점 중 제일 최솟값의 인덱스를 u에 대입
        found[u] = true;                //u 인덱스에 해당되는 정점을 방문했다고 표시
        for(int w = 0; w < n; w++)      //0부터 끝 정점까지 반복
            if(!found[w])               //해당 정점이 방문되지 않았으면
                if( distance[u] + weight[u][w] < distance[w] ) //u 정점을 거쳐서 w정점으로 가는 길이 바로 w로 가는 길보다 짧으면 (가중치가 낮으면)
                    distance[w] = distance[u] + weight[u][w];   //w까지의 가중치 값을 u정점을 거쳐서 w정점으로 가는 가중치 값으로 바꾼다
        
    }
   
}



int main(int argc, const char * argv[]) {
    shortest_path(0, MAX_VERTICES);
    
    return 0;
}
