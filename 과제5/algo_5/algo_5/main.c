//
//  main.c
//  algo_5
//
//  Created by James Choi on 07/10/2019.
//  Copyright © 2019 James Choi. All rights reserved.
//
#include<stdio.h>
#include<stdlib.h>
#define INF 987654321
#define N 5
/*
int W[N][N] = {
    {0, 10, 5, INF, INF},
    {INF, 0, 2, 1, INF},
    {INF, 3, 0, 9, 2},
    {INF,INF,INF, 0, 4},
    {7,INF, INF, 5, 0}
};

int D[N][N] = {
    {0, 10, 5, INF, INF},
    {INF, 0, 2, 1, INF},
    {INF, 3, 0, 9, 2},
    {INF,INF,INF, 0, 4},
    {7,INF, INF, 5, 0}
};
*/
int W[N][N] = {
    {0, 4, INF, INF, INF},
    {5, 0, 7, INF, INF},
    {INF, INF, 0, 10, 5},
    {1,INF,INF, 0, 2},
    {9,2, INF, 3, 0}
};

int D[N][N] = {
    {0, 4, INF, INF, INF},
    {5, 0, 7, INF, INF},
    {INF, INF, 0, 10, 5},
    {1,INF,INF, 0, 2},
    {9,2, INF, 3, 0}
};
 
//경로에 대한 비용
int P[N][N] = {0}; //각 정점 직전에 연결되있는 정점

void floyd2(void);
void path(int, int);

void path(int q, int r){
    printf("path(%d, %d) =%d\n", q, r, P[q][r]);
    if(P[q][r] != 0){
        path(q, P[q][r]);
        printf("[V%d] -> \n", P[q][r]);
        path(P[q][r],r);
    }
}

void floyd2(){
    for(int k=0; k<N; k++){
        for(int i=0; i<N; i++){
            for(int j=0; j<N; j++){
                if(D[i][k] + D[k][j] <  D[i][j]){
                    P[i][j] = k;
                    D[i][j] = D[i][k] + D[k][j];
                }
            }
        }
    }
}

void print_table(int A[N][N]){
    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++){
            if(A[i][j] == INF)
                printf("INF\t");
            else
                printf("%d\t", A[i][j]);
            if(j == 4)
                printf("\n");
        }
    }
}
int main(int argc, char* argv[]) {
    int q, r;
    
    printf("출발점을 입력하시오: ");
    scanf("%d", &q);
    printf("도착점을 입력하시오: ");
    scanf("%d", &r);
    floyd2();
    
    printf("\n\ntable W\n");
    print_table(W);
    printf("\n\ntable D\n");
    print_table(D);
    printf("\n\ntable P\n");
    print_table(P);
    
    printf("\n\n[V%d] -> \n", q);
    path(q,r);
    printf("[V%d]\n", r);
    
    return 0;

}
