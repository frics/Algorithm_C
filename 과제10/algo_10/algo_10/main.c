//
//  main.c
//  algo_10
//
//  Created by James Choi on 2019/11/18.
//  Copyright © 2019 James Choi. All rights reserved.
//

#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#define MAX 8
#define TRUE 1
#define FALSE 0
int *col;

int promising(int i) {
    int k;
    int result;
    k = 1;
    result = TRUE;
    while (k < i&&result){
        if (col[i] == col[k] || abs(col[i] - col[k]) == i - k)
            result = FALSE;
        k++;
    }
    return result;
}

int estimate_n_queens (int n) {
    int i, j, k, m, v;  //  i 노드의 깊이, m = 유망한 자식 노드의 개수
    int mprod, numnodes,index; //mprod = 현재 레벨의 유망한 자식 수
    int prom_children[MAX+1]= {0,};
    
    i=0; //루트노드 lv 0
    numnodes=1; //루트 노드 1개 있어서 numnode가 1개
    m=1;
    mprod=1;
    index = 0;
    
    while (m != 0 && i!=n) {
        mprod = mprod*m; //
        numnodes = numnodes + mprod*n;
        i++;  //다음 레벨로 넘어감
        m = 0;
        
        for(k=1; k<=MAX; k++){
            prom_children[k]=0;
        }
        for (j=1; j<=n; j++) {
            col[i] = j;
            if (promising(i)) {
                prom_children[m] =j;  //유망한 자식들의 위치를 표시한다.
                m++;
            }
        }
        if(m!=0){
            for(k=1; k<=MAX; k++){
                if(prom_children[k] != 0) //랜덤으로 다음 넘어갈 노드를 정해야되는데 index값으로 결정
                    index++;
            }
            if(index == 0)
                index=1;
            v = (rand()%index) + 1;
            j = prom_children[v];
            col[i] = j;
            index = 0;
            }
        }
    return numnodes;
}



int main() {
    
    int i, cnt = 0;
    int total = 0;
    
    col = (int*)malloc(sizeof(int) * (MAX+1));
    printf("monte carlo를 이용하여 n queen 문제 효율 추정하기\n");
   for (i = 0; i < 20; ++i) {
       int nodes = estimate_n_queens(MAX);
       printf("%2d run : %d개\n", i+1, nodes);
       if (nodes) {
           total += nodes;
           cnt++;
       }
   }
    printf("평균 노드 개수 : %d\n", total/20);
    
    free(col);
    
}
