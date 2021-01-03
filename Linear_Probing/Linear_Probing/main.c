//
//  main.c
//  Linear_Probing
//
//  Created by APPLE on 16/07/2020.
//  Copyright © 2020 DataStructure. All rights reserved.
//

//책에 쓰여진 코드를 기반으로 삭제함수를 추가하였다
// 위키의 알고리즘으로 쓴 코드
// 삭제 함수 안에 이동 함수를 구현한다
// 삭제한 해시 테이블 뒤의 해시 테이블이 비어있지 않으면 계속 탐색
// 값이 있는 해시 테이블의 요소 해시값이 해시 테이블의 인덱스 보다 작거나 같으면 삭제된 해시테이블에 옮긴다
// 값이 옮겨진 바로 뒤의 테이블도 같은 알고리즘을 반복한다



// 결론 : 완벽 그자체의 코드 ( 완벽한 삭제 함수)
// - 아님 완벽하지 않음
// ex : insert a, insert 10, insert n, insert c, delete a, insert c 를 해보면 알거임
// - 아직 해결못함
//해결 방안 1 : 가장 적절한 해결책은 삭제될 슬롯에 있는 값과 같은 해시값을 가지는 클러스터의 마지막 슬롯을 삭제될 슬롯으로 가져와서 클러스터의 손상을 막는 방법이다.
//출처: https://ict-nroo.tistory.com/76 [개발자의 기록습관]

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define KEY_SIZE 10     //탐색 키의 최대 길이
#define TABLE_SIZE 13   //해시 테이블의 크기 = 소수
#define empty(e) strlen(e.key) == 0         //현재 버켓이 비어 있으면 1
#define equal(e1, e2) !strcmp(e1.key, e2.key)   //두개의 항목이 동일하면 1

typedef struct{
    char key[KEY_SIZE];
    bool deleted;
    //다른 필요한 필드들을 여기에 넣는다
}element;


//해시 테이블 초기화
void init_table(element ht[])
{
    for(int i = 0; i < TABLE_SIZE; i++){
        ht[i].key[0] = NULL;
        ht[i].deleted = false;
    }
}

//문자로 된 탐색 키를 숫자로 변환 (문자들의 아스키값 합산)
int transform(char *key)
{
    int number = 0;
    while(*key)         //간단한 덧셈 방식 사용 자연수 생성
        number += *key++;   //각 문자의 아스키코드를 number 에 합한다
    return number;          //아스키코드의 합산 리턴
}

//제산 함수를 사용한 해싱 함수
int hash_function(char *key)
{
    return transform(key) % TABLE_SIZE; //아스키코드의 합을 테이블 수로 나눈 나머지 값 리턴
}

//선형조사법을 이용하여 테이블에 키를 삽입하고
//테이블이 가득 찬 경우는 종료
void hash_lp_add( element item, element ht[])
{
    int i, hash_value;
    
    hash_value = i = hash_function(item.key);   //item의 해시함수를 해시값과 i에 저장
    while (!empty(ht[i])) {     //해당되는 해시 테이블이 비어있지 않다면(이미 같은 해시값의 요소가 저장되어 있다면)
        if(equal(item,ht[i])){  //해시테이블의 요소와 추가하려는 요소가 같다면
            fprintf(stderr, "탐색 키가 중복되었습니다\n");
            return;
        }
        i = (i + 1) % TABLE_SIZE;   //다른 값이면 다음 해시 테이블로 이동
        if(i == hash_value){        //해시 테이블 모두 조사한 후 다시 처음 위치로 돌아왔으면
            fprintf(stderr, "테이블이 가득찼습니다\n");
            return;
        }
    }
    ht[i] = item;   //해시테이블이 비어 있다면 그곳에 item을 추가한다
    ht[i].deleted = false;
    
}




//선형조사법을 이용하여 테이블에 저장된 키를 탐색
void hash_lp_search(element item, element ht[])
{
    int i, hash_value;
    hash_value = i = hash_function(item.key); //item의 해시함수를 해시값과 i에 저장
    while (!empty(ht[i]) || ht[i].deleted) { //해당되는 해시 테이블이 비어있지 않다면(같은 해시값의 요소가 저장되어 있다면)
        if(equal(item, ht[i])){ //해시 테이블 안의 값과 item 요소의 값이 같다면
            fprintf(stderr, "탐색성공 : 위치 = %d\n",i);
            
            return;
            
        }
        i = (i + 1) % TABLE_SIZE; // 다른 값이면 다음 해시 테이블로 이동
        if(i == hash_value){      //해시 테이블 모두 조사한 후 다시 처음 위치로 돌아왔으면
            fprintf(stderr, "찾는 값이 테이블에 없음\n");
            return;
        }
    }
    
    //해시테이블이 비어있지만 찾는 값이 아닐때
    fprintf(stderr, "찾는 값이 테이블에 없음\n");
    
}


void hash_lp_delete(element item, element ht[])
{
    int i , hash_value, deleted_index , empty_index;
    hash_value = i = hash_function(item.key);
    while (!empty(ht[i]) || ht[i].deleted) {
        if(equal(ht[i], item)){
            printf("%s 삭제\n", item.key);
            ht[i].key[0] = NULL;
            ht[i].deleted = true;
            // Following code is edited
            
            deleted_index = i++;    //삭제된 해시테이블의 인덱스를 deleted_index에 명시하고 i를 하나 증가한다
            empty_index = deleted_index;    //empty_index : 비어있는 인덱스를 명시
            
            while (!empty(ht[i])) {
                if(hash_function(ht[i].key) <= deleted_index){
                    ht[empty_index++] = ht[i];
                    ht[i].key[0] = NULL;
                    ht[i++].deleted = true;
                }
                else ++i;
                
                
            }
            
            return;
        }
        i = (i + 1) % TABLE_SIZE;
        if(i == hash_value){
            printf("삭제하려는 값이 테이블에 없습니다\n");
            return;
        }
        
    }
    printf("삭제하려는 값이 테이블에 없습니다\n");
    
}


void hash_lp_print(element ht[])
{
    for(int i = 0; i < TABLE_SIZE; i++)
        printf("[%d]    %s\n", i , ht[i].key);
}


int main(int argc, const char * argv[]) {
    element tmp;
    element hash_table[TABLE_SIZE]; //해시 테이블
    init_table(hash_table);
    int op;
    while (1) {
        printf("원하는 연산을 입력하시오 ( 0 = 입력, 1 = 탐색, 2 = 삭제, 3 = 종료)\n");
        scanf("%d",&op);
        if(op == 3) break;
        printf("키를 입력하시오 = ");
        scanf("%s",tmp.key);
        if (op == 0)
            hash_lp_add(tmp, hash_table);
        else if(op == 1)
            hash_lp_search(tmp, hash_table);
        else
            hash_lp_delete(tmp, hash_table);
        hash_lp_print(hash_table);
        
    }
    return 0;
}
