//
//  main.c
//  UOS_17_hash
//
//  Created by APPLE on 26/08/2020.
//  Copyright © 2020 DataStructure. All rights reserved.
//
//정수로만 이루어진 해쉬 체이닝
//2017년도 서울시립대


#include <stdio.h>
#include <stdlib.h>

#define HSZ 127
#define HASHING(x) ((x)%HSZ)

struct node_t{
    int val;
    struct node_t *next;
}node_t;

struct node_t hash_table[HSZ];

void init(){
    for(int i = 0; i < HSZ; i++){
        hash_table[i].next = NULL;
        
    }
}

void insert_hash(int value){
    int hash_value = HASHING(value);
    struct node_t *node_before = NULL;
    struct node_t *node = hash_table[hash_value].next;
    while (node) {
        if(node->val > value)
            break;
        node_before = node;
        node = node->next;
    }
    
    struct node_t *new = (struct node_t*)malloc(sizeof(struct node_t));
    if(new == NULL){
        fprintf(stderr, "메모리 할당 오류");
        return;
    }
    new->val = value;
    new->next = NULL;
        
    if(node_before)
        node_before->next = new;
    else
        hash_table[hash_value].next = new;
    new->next = node;
    
    
}

int hash_delete(int value){
    int hash_value = HASHING(value);
    int result = 0;
    struct node_t *node_before = NULL;
    struct node_t *node = hash_table[hash_value].next;
    while (node) {
        if(node->val == value){
            result = 1;
            if(node_before)
                node_before->next = node->next;
            else
                hash_table[hash_value].next = node->next;
            
            free(node);
            break;
        }
        node_before = node;
        node = node->next;
    }
    
    
    
    
    return result;
}

void print_hash(){
    struct node_t *node;
    printf("\n");
    for (int i = 0 ; i < HSZ; i++) {
        printf("[%d]",i);
        node = hash_table[i].next;
        while(node){
            printf(" -> %d",node->val);
            node = node->next;
        }
        printf("\n");
    }
}

int main(){
    init();
    insert_hash(1);
    insert_hash(128);
    
    
    print_hash();
    printf("hash_delete = %d",hash_delete(1));
    
    print_hash();
    return 0;
    
}

