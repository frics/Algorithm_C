//
//  main.c
//  tsp2
//
//  Created by James Choi on 2019/11/04.
//  Copyright © 2019 James Choi. All rights reserved.
//

#include <stdio.h>
#include<string.h>
#define MAX 987654321
//#define MIN(a,b) (((a)<(b)) ? (a): (b))
int W[6][6] = {
{0, 8, 13, 18, 20},
{3, 0, 7, 8, 10},
{4, 11, 0, 10, 7},
{6, 6, 7, 0, 11},
{10, 6, 2, 1, 0}};

int D[16][65536] = {MAX, };
int minlen;// = MAX;


int minimum(int a, int b)
{
    return (((a) < (b)) ? (a) : (b));
}
 
void travel(int start, int visit){
    int i;
    
    if(visit == (1<<5)-2){
        minlen = minimum(minlen, D[start][visit]+W[start][1]);
        return;
    }
    
    for(i=1; i<=5; i++){
        if((!((1<<i)&visit)) && W[start][i]){
            if(D[i][visit|(1<<i)] > D[start][visit]+W[start][i]){
                D[i][visit|(1<<i)] = D[start][visit]+W[start][i];
                travel(i, (visit|(1<<i)));
            }
        }
    }
}
int main() {
    D[1][1<<1] = 0;
    travel(1,1);
    printf("%d", minlen);
    return 0;
}
