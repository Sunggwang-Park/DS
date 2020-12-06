//
//  main.c
//  Floyd_Book
//
//  Created by APPLE on 16/07/2020.
//  Copyright © 2020 DataStructure. All rights reserved.
//


#include <stdio.h>

#define INF 1000
//#define min(a,b) (a > b)? b : a
#define V 7


void print_floyd(int[][V]);

void floyd(int weight[][V])
{
    int A[V][V];
    
    for (int i = 0; i < V; i++)     //가중치 행렬을 A 2차원 배열에 저장
        for(int j = 0; j < V; j++)
            A[i][j] = weight[i][j];
    
    for(int k = 0; k < V; k++)
        for(int i = 0; i < V; i++)
            for(int j = 0; j < V; j++)
                if(A[i][j] > A[i][k] + A[k][j])
                    A[i][j] = A[i][k] + A[k][j];
  //                A[i][j] = min(A[i][j], A[i][k] + A[k][j]);
    
    print_floyd(A);
    

}

void print_floyd(int a[][V])
{
    printf("\t");
    for(int i = 0; i < V; i++)
        printf("%d\t",i);
    printf("\n");
    
    for(int i = 0; i < V; i++){
        printf("%d\t",i);
        for(int j = 0; j < V; j++)
            printf("%d\t",a[i][j]);
        printf("\n");
        
        
    }
}

int main(int argc, const char * argv[]) {
    int weight[V][V] = {  //네트워크의 인접 행렬
        { 0, 7, INF, INF,   3,  10, INF },
        { 7, 0,   4,  10,   2,   6, INF },
        {INF, 4,  0,   2, INF, INF, INF },
        {INF, 10, 2,   0,  11,  9,    4 },
        {  3,  2, INF, 11,  0,  INF,  5 },
        { 10,  6, INF, 9,  INF,  0,  INF },
        { INF, INF, INF,  4,  5, INF, 0  }
    };
    
    floyd(weight);

    return 0;
}
