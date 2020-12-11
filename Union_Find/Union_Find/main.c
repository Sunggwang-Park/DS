//
//  main.c
//  Union_Find
//
//  Created by APPLE on 14/10/2020.
//  Copyright © 2020 DataStructure. All rights reserved.
//

#include <stdio.h>

#define MAX_SIZE 10

int parent[MAX_SIZE];
int rank[MAX_SIZE];

//부모배열 초기화
//정점의 부모가 없을때는 부모노드가 자기 자신이다.
//랭크 배열 모두 1로 초기화
void init(){
    for (int i = 0; i < MAX_SIZE; i++){
        parent[i] = i;
        rank[i] = 1;
    }
    
}

int find(int x){
    
    if(parent[x] == x)  //부모노드가 자기 자신일 경우 자신의 값 리턴
        return x;
    int y = find(parent[x]);
    parent[x] = y;          //노드 최적화
    return y;
}


void Union(int x, int y){
    x = find(x);
    y = find(y);
    
    //두 값이 같다는 의미는 union할 시에 사이클이 생긴다는 의미이다. 그러므로 return으로 멈춰준다
    if(x == y)
        return;
    
    if(rank[x] > rank[y]){
        parent[y] = x;
        rank[x] += rank[y];
    }
    else{
        parent[x] = y;
        rank[y] += rank[x];
    }
}




int main(int argc, const char * argv[]) {
    
    init();
    
    return 0;
}
