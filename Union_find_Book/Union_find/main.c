//
//  main.c
//  Union_find
//
//  Created by APPLE on 13/07/2020.
//  Copyright © 2020 DataStructure. All rights reserved.
//

#include <stdio.h>

#define MAX_VERTICES 50

//parent 배열과 num배열을 GraphNode에 멤버 변수로 지정하면
//전역 변수로 쓰지 않아도 될 것 같다
int parent[MAX_VERTICES];   //부모 노드
int num[MAX_VERTICES];  //각 집합의 크기 - i라는 노드가 속한 집합의 노드들의 총 개수를 의미한다

//초기화
//집합의 원소를 하나씩 분리하여 독자적인 집합을 만든다
void set_init(int n)    // n : 노드의 개수
{
    int i;
    for (i = 0; i < n; i++) {
        parent[i] = -1;
        num[i] = 1;
    }
}

//vertex가 속하는 집합을 반환한다.
//자세히 말하면 vertex가 속하는 집합의 모든 노드들의 부모를 집합의 루트 노드로
//설정하고 그 루트 노드의 값을 반환한다
int set_find(int vertex)
{
    int p, s, i = -1;       // p : 노드의 부모배열  s : 현재 함수에서 return 되는 값,
                            // s는 집합의 루트를 의미한다, i : 왜 -1로 초기화하는지 아직 모르겠다
    for(i = vertex; (p = parent[i]) >= 0; i=p);  //루트 노드까지 반복
    
    s = i;      //집합의 대표 원소, 즉 집합의 루트노드이다
    
    for(i = vertex; (p = parent[i]) >= 0; i = p)
        parent[i] = s;          //집합의 모든 원소들의 부모를 s로 설정
    
    return s;
    
}

void set_union(int s1, int s2)
{
    if(num[s1] < num[s2]){      //s1이 속한 집합의 노드들의 개수가
                                //s2가 속한 집합의 노드들의 개수보다 작을 때
        parent[s1] = s2;        //s1의 부모를 s2로 설정한다
        num[s2] += num[s1];     //s2가 속한 집합의 노드들의 개수에 s1이 속한 집합의 노드들의 개수를 더한다
    }
    
    else{                       //s1이 속한 집합의 노드들의 개수가
                                //s2가 속한 집합의 노드들의 개수보다 클 때
        parent[s2] = s1;        //s2의 부모를 s1으로 설정한다
        num[s1] += num[s2];     //s1이 속한 집합의 노드들의 개수에 s2가 속한 집합의 노드들의 개수를 더한다
        
    }
}

int main(int argc, const char * argv[]) {
    // insert code here...
    printf("Hello, World!\n");
    return 0;
}
