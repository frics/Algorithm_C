//
//  main.c
//  algo_10_sos
//
//  Created by James Choi on 2019/11/19.
//  Copyright © 2019 James Choi. All rights reserved.
//

#include <stdio.h>
#include<stdlib.h>
#include<time.h>

#define TRUE 1
#define FALSE 0
const int w[6] = {2, 10, 13, 17, 22, 42};
int tmp_w[6] = { 2, 10, 13, 17, 22,42 };
int include[6] = { 0,};
int tmp_include[6]={0,};
int W =52;

int chs; //1개의 부분집합을 구할때와 전부 구할때를 구분하기 위해 선언

int promissing(int i, int weight, int total){
    if((weight+total > W) && (weight == W || weight + w[i+1] <=W))
        return TRUE;
    else
        return FALSE;
}
void print(){
    printf("sum of sub of set\n");
    for(int i=0; i<6; i++){
        if(include[i] != 0)
            printf("incldue[%d]: %d\n", i, include[i]);
    }
    printf("--------------\n");
    chs++; // 1개의 부분집합 탐색을 완료하고 출력하면 증가
}
void sum_of_subsets(int i, int weight, int total){
    if(promissing(i, weight, total)){ //유망 여부를 확인하여 탐색을 실행한다.
        
        if(chs == 3) //초기 입력값 2에서 1개의 부분집합의 합을 구했을때 3으로 증가하여 함수 종료
            return;
        
        if(W==weight)//탐색을 완료했을때 출력한다.
            print();
        
        else{ //재귀적으로 실행하여 backtracking한다.
            //가중치를 포함했을 경우
            include[i+1]=w[i+1];
            sum_of_subsets(i+1, weight+w[i+1], total-w[i+1]);
            include[i+1]=0;
            //가중치를 포함 안했을 경우
            sum_of_subsets(i+1, weight, total-w[i+1]);
        }
    }
    
}
int estimate_sum_of_subsets(int n) {
    
    int i;
    int j;
    int k;
    int m;
    int mprod;
    int numnodes; //탐색에 소비한 노드 개수를 담는다
    int weight = 0;
    int total = 106;
    int prom_children[2] = { 0,};//현재깊이에서 유망한자식노드값 저장
    int F = FALSE; //유망한지 판별
    
    i = 0;
    numnodes = 1;
    m = 1;
    mprod = 1;
    
    while (m != 0 && i != 2) {//level 이n 의안에있을때동작하도록
        mprod *= m;
        numnodes += mprod * 2;
        i++;
        m = 0;
        for (k = 0; k < 2; k++) {//초기화시켜주는과정.
            if (k == 0) {
                prom_children[k] = 0;// 0으로초기화
            }
        }//자식마디초기화
        
        for (j = 0; j < 2; j++) {
            if (tmp_w[j] != 0) {
                tmp_include[i] = j;
                if (promissing(i, weight, total)) {//promising확인 후 포함
                    m++;
                    prom_children[j] = tmp_w[j];
                
                }
            }
        }
        if (m != 0) { //monte carlo핵심인 난수 지정하여 경로 설정
            while (F == FALSE) {
                
                j = rand() % 2;     //랜덤으로수결정
                if (prom_children[j] != 0) { //promissing할때 F값 true 반환
                    F = TRUE;
                }
            }
            tmp_include[i] = j;
            tmp_w[j] = 0;
            weight += prom_children[j];
            total -= prom_children[j];
            F = FALSE;
        }
    }
    
    return numnodes;  // 탐색에 소비한 노드 개수 반환
}
int main() {
    int numnode =0, total_numnode = 0;
    int total =0;
    srand((unsigned int)time(NULL));
    clock_t start, end;
    float run_time, run_sum=0;
    
    printf("1. 모든 부분 집합의 합 구하기\n2. 한개의 부분 집합의 합 구하기\n3. monte carlo를 이용하여 효율 추정\n입력 : ");
    scanf("%d", &chs);
    
    switch (chs) {
        case 1:
        case 2:
            printf("\nBackTracking을 이용하여 부분 집합의 합 구하기\n");
            for(int i =0; i<6; i++)
                total+=w[i];
            start = clock();
            sum_of_subsets(0, 0, total);
            end = clock();
            run_time = (float)(end - start);
            printf("run time : %.3f ms\n", run_time);
            break;
            
        default:
            printf("monte carlo를 이용하여 효율 추정하기\n");
            for (int i = 0; i < 20; i++){  //n queen과 동일하게 더욱 정확한 효율 추정을 위해 20번 반복한다
                
                start = clock();
                numnode = estimate_sum_of_subsets(6);
                end= clock();
                run_time = (float)(end - start);
                run_sum +=run_time;
               
                printf("%d run : %d개\n", i + 1, numnode);
        
                for (int p = 0; p < 6; p++){//추정값 획득을 위해 함수 실행시 변환되는 값을 다시 원상태로 돌려준다.
                    
                    tmp_w[p] = w[p];
                    tmp_include[p] = include[p];
                    }
                total_numnode += numnode;
                }
            printf("평균 노드 개수 : %d개\n", total_numnode / 20);
            printf("평균 수행시간 : %.3fms\n", run_sum/20);
            break;
    }
    
}
