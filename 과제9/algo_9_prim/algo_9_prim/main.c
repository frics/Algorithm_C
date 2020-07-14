//
//  main.c
//  algo_9_prim
//
//  Created by James Choi on 2019/11/11.
//  Copyright © 2019 James Choi. All rights reserved.
//
#include <stdio.h>
#define TRUE 1
#define FALSE 0

#define MAX 10  //노드의 개수
#define INF 987654321

int W[MAX][MAX]={ //해당 그래프의 인접행렬, 직접 연결되있지 않으면 INF로 표기
{ 0, 32, INF, 17, INF, INF, INF, INF, INF, INF },
   { 32, 0, INF, INF, 45, INF, INF, INF, INF, INF },
   { INF, INF, 0, 18, INF, INF, 5, INF, INF, INF },
   { 17, INF, 18, 0, 10, INF, INF, 3, INF, INF },
   { INF, 45, INF, 10, 0, 28, INF, INF, 25, INF },
   { INF, INF, INF, INF, 28, 0, INF, INF, INF, 6 },
   { INF, INF, 5, INF, INF, INF, 0, 59, INF, INF },
   { INF, INF, INF, 3, INF, INF, 59, 0, 4, INF },
   { INF, INF, INF, INF, 25, INF, INF, 4, 0, 12 },
   { INF, INF, INF, INF, INF,6,INF,INF,12,0 } };

int nearest[MAX];
int distance[MAX];


int get_min_vertex(int n){ //최소 distance[v] 값을 갖는 정점을 반환
    int v = 0,i;

    for (i = 0; i <n; i++){
        if (!nearest[i]){
            v = i;
            break;
        }
    }
    
    for (i = 0; i < n; i++)// 연결하지 않은 간선들 중 최소 가중치값을 갖는 정점을 찾음
    {
        if( !nearest[i] && (distance[i] < distance[v]))
            v = i;
    }

    return (v);
}

void prim(int start)
{
    int i, j, v;
    int sum=0;

    for(j=0;j<MAX;j++){ //초기화
        distance[j]=INF;
    }
    distance[start]=0;
    for(i=0;i<MAX;i++){
        j = get_min_vertex(MAX);
        nearest[j]=TRUE; // 지나간 경로 체크
         
        if( distance[j] == INF )
            return;
             
        printf("[V%d]연결 weight : %d\n", j+1, distance[j]);
        sum+=distance[j]; //총거리를 구하기 위해 나온 거리를 계속 더해줌

        for( v=0; v<MAX; v++){
            if( W[j][v]!= INF){
                if( !nearest[v] && W[j][v]< distance[v] )
                    distance[v] = W[j][v]; // 간선의 거리를 갱신
            }
        }
    }
    printf("MST by Prim's algoritm : %d\n", sum);
}

int main()
{
    prim(0);
}

