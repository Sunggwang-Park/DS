//
//  main.c
//  Weighted_Union_Find
//
//  Created by APPLE on 14/10/2020.
//  Copyright © 2020 DataStructure. All rights reserved.
//



#define MAX_SIZE 10

int parent[MAX_SIZE];

void init(){
    for (int i = 0; i < MAX_SIZE; i++)
        parent[i] = -1;
}

int find(int x){
    if(parent[x] < 0)
        return x;
    int y = find(parent[x]);
    parent[x] = y;
    return y;
}

void Union(int x, int y){
    x = find(x);
    y = find(y);
    
    if(x == y)
        return;
    
    if(parent[x] < parent[y]){
        parent[y] = x;
        parent[x] += parent[y];
    }
    else{
        parent[x] = y;
        parent[y] += parent[x];
    }
}

int main(int argc, const char * argv[]) {
    init();
    return 0;
}
