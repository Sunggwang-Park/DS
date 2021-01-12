//
//  main.c
//  Prim_Geeks
//
//  Created by APPLE on 14/07/2020.
//  Copyright © 2020 DataStructure. All rights reserved.
//

//Geeksforgeeks 에서 가져온 prim 알고리즘
//prim의 로직은 비슷하다
//good : 최소 값을 반환하는 minkey의 for루프가 책보다 더 간결하다
//bad : 간선이 없으면 0으로 표시하여서 간선의 가중치가 0일 경우를 구현못한다

//총평 : 가장 좋은 로직인듯 ?

// A C program for Prim's Minimum
// Spanning Tree (MST) algorithm. The program is
// for adjacency matrix representation of the graph
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
// Number of vertices in the graph
#define V 5

// A utility function to find the vertex with
// minimum key value, from the set of vertices
// not yet included in MST
int minKey(int key[], bool mstSet[])    // 최소 값을 갖는 정점의 인덱스 반환
{
    // Initialize min value
    int min = INT_MAX, min_index = 0;
    
    for (int v = 0; v < V; v++)
        if ( !mstSet[v] && key[v] < min){
            min = key[v];
            min_index = v;
        }
    
    return min_index;
}

// A utility function to print the
// constructed MST stored in parent[]
void printMST(int parent[], int graph[V][V])
{
    printf("Edge \tWeight\n");
    for (int i = 1; i < V; i++)
        printf("%d - %d \t%d \n", parent[i], i, graph[i][parent[i]]);
}

// Function to construct and print MST for
// a graph represented using adjacency
// matrix representation
void primMST(int graph[V][V])
{
    // Array to store constructed MST
    int parent[V];
    // Key values used to pick minimum weight edge in cut
    int key[V];
    // To represent set of vertices included in MST
    bool mstSet[V];         //정점이 selected되었는지 확인하는 bool 배열
    //TRUE : MST에 포함 되었음, FALSE : MST에 포함 안 되었음
    
    // Initialize all keys as INFINITE
    for (int i = 0; i < V; i++){
        key[i] = INT_MAX;
        mstSet[i] = false;
    }
    
    // Always include first 1st vertex in MST.
    // Make key 0 so that this vertex is picked as first vertex.
    key[0] = 0;
    parent[0] = -1; // First node is always root of MST
    
    // The MST will have V vertices
    for (int count = 0; count < V - 1; count++) {
        // Pick the minimum key vertex from the
        // set of vertices not yet included in MST
        int u = minKey(key, mstSet);
        
        // Add the picked vertex to the MST Set
        mstSet[u] = true;
        
        // Update key value and parent index of
        // the adjacent vertices of the picked vertex.
        // Consider only those vertices which are not
        // yet included in MST
        for (int v = 0; v < V; v++)
            
            // graph[u][v] is non zero only for adjacent vertices of m
            // mstSet[v] is false for vertices not yet included in MST
            // Update the key only if graph[u][v] is smaller than key[v]
            if (graph[u][v] && !mstSet[v] && graph[u][v] < key[v]){
                parent[v] = u;
                key[v] = graph[u][v];
            }
    }
    
    // print the constructed MST
    printMST(parent, graph);
}

// driver program to test above function
int main()
{
    /* Let us create the following graph
     2 3
     (0)--(1)--(2)
     | / \ |
     6| 8/ \5 |7
     | /     \ |
     (3)-------(4)
     9         */
    int graph[V][V] = { { 0, 2, 0, 6, 0 },
        { 2, 0, 3, 8, 5 },
        { 0, 3, 0, 0, 7 },
        { 6, 8, 0, 0, 9 },
        { 0, 5, 7, 9, 0 } };
    
    // Print the solution
    primMST(graph);
    
    return 0;
}


