//
//  main.c
//  algo7_TSP
//
//  Created by James Choi on 2019/10/30.
//  Copyright © 2019 James Choi. All rights reserved.

#include <stdio.h>
#define MAX 10000000

int W[5][5] = {
   {0, 8, 13, 18, 20},
   {3, 0, 7, 8, 10},
   {4, 11, 0, 10, 7},
   {6, 6, 7, 0, 11},
   {10, 6, 2, 1, 0}};

int D[5][1<<5] ={MAX};

int minimum(int a, int b)
{
    return a < b ? a : b;
}

int travel(int start, int visit)
{
    int i=0;
    if (visit == (1 << 5) - 1)
        return W[start][0];
    
    int min = 0;
    if (min != 0)
        return min;
    min = MAX;
    for (i = 0; i <= 5; i++)
        {
        if (visit&(1 << i))
            continue;
        if (W[start][i] == 0)
            continue;
        min = minimum(min, travel(i, visit | (1 << i)) + W[start][i]);
        }
    return min;
}


int main() {
    int minlen = 0;
    minlen = travel(0, 1);
    printf("V1에서 모든 정점을 거쳐 다시 V1로 돌아오는 최소 경로는  %d 이다. \n", minlen);
    return 0;
}
