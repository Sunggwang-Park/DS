//
//  main.c
//  Dijkstra_Shortest_path
//
//  Created by APPLE on 15/07/2020.
//  Copyright © 2020 DataStructure. All rights reserved.
//

//가장 간단한 다익스트라 알고리즘은 꼭짓점 집합 Q를 일반적인 연결 리스트나 배열로 저장하고, extract-minimum은 단순히 Q에 있는 모든 꼭짓점의 선형 탐색이다. 따라서 이 경우에 실행 시간은 {O(|E|+|V|^{2})=O(|V|^{2})}이다.
//
//    변이 {|V|^{2}}{|V|^{2}}보다 한참 적은 희소 그래프에 대해서는, 다익스트라 알고리즘은 그래프를 인접 리스트의 형태로 저장하고 최소 추출을 효율적으로 하기 위해서 우선순위 큐로 자가 균형 이진 탐색 트리, 이진 힙, 페어링 힙, 또는 피보나치 힙을 사용해서 효율적으로 수행할 수 있다. decrease-key 단계를 이진 힙으로 효율적으로 수행하기 위해서는 각각의 꼭짓점에서 힙의 위치로 연결하는 보조 자료 구조를 사용하고 우선순위 큐 Q가 바뀔 때 마다 갱신할 필요가 있다. 자가 균형 이진 탐색 트리나 이진 힙에서 다익스트라 알고리즘은 최악의 경우에 다음의 시간이 필요하다({\displaystyle \log }\log 는 이진 로그 {\displaystyle \log _{2}}\log _{2}를 의미한다):
//
//    {\displaystyle \Theta ((|E|+|V|)\log |V|)}{\displaystyle \Theta ((|E|+|V|)\log |V|)}
//    연결 그래프에서는 이 시간 상한을 {\displaystyle \Theta (|E|\log |V|)}{\displaystyle \Theta (|E|\log |V|)}로 단순화 할 수 있다. 피보나치 힙은 이 시간을 다음과 같이 개선시킬 수 있다:
//
//    {\displaystyle O(|E|+|V|\log |V|)}{\displaystyle O(|E|+|V|\log |V|)}.

//최소 가중치를 구하는 부분을 우선순위 큐로 구현하면 더 효율적일 수 있다
//add_with_priority(), decrease_priority() 그리고 extract_min() 이 필요하다
// 이 세가지 연산을 수행하는 최적의 힙은 '피보나치 힙'이다


#include <limits.h>
#include <stdio.h>
#include <stdbool.h>

#define MAX_VERTICES 7      //정점의 수
#define INF 1000            //무한대(연결이 없는 경우) - 가중치의 최댓값보다 큰 값으로 지정




int min_distance(int distance[], int n, int found[])  //distance 배열안에서 선택안된 정점 중 최솟값의 인덱스를 반환하는 함수
{
    int min = INT_MAX, minpos = -1; //INT_MAX : 2147483647  - 최대 정수 (limits.h 파일 사용)
    for (int i = 0; i < n; i++)
        if(distance[i] < min && !found[i]){
            min = distance[i];
            minpos = i;
        }
    
    return minpos;

}
void print_Dijkstra(int distance[], int n)
{
    printf("0 정점에서 \n");
    for (int i = 1; i < n; i++) {
        printf("%d 정점까지의 최단거리 : %d\n", i, distance[i]);
    }
}
void dijkstra(int weight[][MAX_VERTICES], int start)
{
    int distance[MAX_VERTICES];     //시작 정점으로부터의 최단 경로 거리
    int found[MAX_VERTICES];        //방문한 정점 표시
    int prev[MAX_VERTICES];         //prev 배열은 소스까지 최단 경로를 찾기 위한 소스 그래프의 "다음" 꼭짓점을 나타내는 배열이다.(각 정점에서 시작 정점까지 최단 경로로 거슬러 올라갈 때의 부모 정점)
  
    
    int u;  //최솟값의 인덱스
    for (int i = 0; i < MAX_VERTICES; i++) {   //초기화
        distance[i] = weight[start][i];     //i항의 열들을 차례대로 distance값에 대입한다
        found[i] = false;                   //아직 발견된 정점이 없으므로 모두 false로 둔다
        prev[i] = start;                    //prev 배열을 모두 start로 설정 (0으로 설정)
    }
    found[start] = true;            //시작 정점 방문 표시
    distance[start] = 0;            //왜 필요하지..? - 시작정점에서 시작정점까지의 거리는 0
    
    for (int i = 0; i < MAX_VERTICES-1; i++) { //시작 정점은 이미 방문되었고 나머지 6개의 정점이 남았으니 0부터 n-2까지 반복한다(6번 반복)
        u = min_distance(distance, MAX_VERTICES, found); //아직 방문되지 않은 정점 중 제일 최솟값의 인덱스를 u에 대입
        found[u] = true;                //u 인덱스에 해당되는 정점을 방문했다고 표시
        for(int w = 0; w < MAX_VERTICES; w++)      //0부터 끝 정점까지 반복
            if(!found[w])               //해당 정점이 방문되지 않았으면
                if( distance[u] + weight[u][w] < distance[w] ){ //u 정점을 거쳐서 w정점으로 가는 길이 바로 w로 가는 길보다 짧으면 (가중치가 낮으면)
                    distance[w] = distance[u] + weight[u][w];   //w까지의 가중치 값을 u정점을 거쳐서 w정점으로 가는 가중치 값으로 바꾼다
                    prev[w] = u;        //w 정점의 최단 경로가 u 정점을 거쳐갔기 때문에 w 정점에서 start 정점까지의 최단 경로에서 w 정점의 부모 정점은 u가 된다.
                }
       
    }
    print_Dijkstra(distance, MAX_VERTICES);
    
    for (int j = 0; j < MAX_VERTICES; j++) {
        printf("%d정점의 prev : %d\n", j, prev[j]);    //각 정점에서 prev을 따라가다 보면 start정점이 나온다
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
