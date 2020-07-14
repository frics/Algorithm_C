//
//  main.c
//  algo_11_dfs
//
//  Created by James Choi on 2019/11/24.
//  Copyright © 2019 James Choi. All rights reserved.
//

#include <stdio.h>
#define TRUE 1
#define FALSE 0
#define N 5 //아이템 갯수
#define W 9 //총 무게
int bestset[N+1]= {0, };
int include[N+1]= {0, };
int maxprofit =0;
int numset =0;
int cnt =1;
/*************************아이템 노드 구조체**********************************/
typedef struct{
    int level;
    int profit;
    int weight;
    int bound;
}node;
/*********************queue******************/
node queue[100];
int head;
int tail;


void enqueue(node n)
{
    queue[tail] = n;
    tail++;
}
node dequeue()
{
    return queue[head++];
}

int empty()
{
    return head == tail;
}
/**********************************************/
int items[N+1][2] = { //아이템값 profit, weight
    {0, 0},
    {20, 2},
    {30, 5},
    {35, 7},
    {12, 3},
    {3, 1},
};

int promising(int i, int profit, int weight){
    int j=0,k=0;
    int totalweight =0;
    int bound;
    
    if (weight>=W)
        return FALSE;
    else{
        j = i+1;
        bound = profit;
        totalweight = weight;
        while((j<N+1) && (totalweight + items[j][1] <= W)){
            totalweight = totalweight+ items[j][1];
            bound = bound +items[j][0];
            j++;
        }
        k = j;
        
        if(k<N)
            bound = bound + (W-totalweight)*items[j][0]/items[j][1];
        return bound>maxprofit;
        
    }
}
void knapsack_DFS(int i, int profit, int weight){
    printf("%d.  %d depth  %d  %d \n", cnt++, i, profit, weight);
    
    if((weight <= W) && (profit > maxprofit)){ //maxprofit 갱신
        maxprofit = profit;
        numset = i;
        for(int k =0; k<N; k++) //매번 갱신해줘야됨
            bestset[k] = include[k];
    }
    if(promising(i, profit, weight)){
        //해당 깊이를 포함했을때
        include[i+1]= 1;
        knapsack_DFS(i+1, profit+items[i+1][0], weight + items[i+1][1]);
        //포함 안했을때
        include[i+1] = 0;
        knapsack_DFS(i+1, profit, weight);
    }
}


int bound(node n){
    int j=0, k=0;
    int totalweight =0;
    int result =0;
    if(n.weight>W)
        return 0;
    else{
        result =  n.profit;
        j = n.level+1;
        totalweight = n.weight;
        while((j<=N) && (totalweight + items[j][1] <= W)){
            totalweight += items[j][1];
            result += items[j][0];
            j++;
        }
        k=j;
        if(k<=N)
            result= result+(W-totalweight)*items[k][0]/items[k][1];
        return result;
    }
}

void knapsack_BFS(){
    node v,u;
    int cnt=1;
    head =0;
    tail=0;
    
    v.level = 0; v.profit =0; v.weight =0;
    maxprofit =0;
    enqueue(v);
    while(!empty()){
        v = dequeue();
        //printf("%d  %d  %d \n", v.level, v.profit, v.weight);
        u.level=v.level+1;
        //포함했을때
        u.weight= v.weight + items[u.level][1];
        u.profit= v.profit + items[u.level][0];
        if((u.weight<=W) && (u.profit> maxprofit))
            maxprofit = u.profit;
        printf("%d. 왼 %d depth  %d  %d  %d \n", cnt++, u.level, u.profit, u.weight, bound(u));
        if(bound(u)>maxprofit)
            enqueue(u);
        //포함안했을때
        u.weight= v.weight;
        u.profit=v.profit;
        printf("%d. 오 %d depth %d  %d  %d\n", cnt++, u.level, u.profit, u.weight, bound(u));
        if (bound(u)>maxprofit)
            enqueue(u);
    }
}

void knapsack_BestFS(){
    node v,u;
    int cnt =1;
    head =0;
    tail=0;
    
    v.level = 0; v.profit =0; v.weight =0;
    maxprofit =0;
    enqueue(v);
    while(!empty()){
        v = dequeue();
        if(v.bound > maxprofit){
            u.level = v.level+1;
            //포함했을때
            u.weight= v.weight + items[u.level][1];
            u.profit= v.profit + items[u.level][0];
            
            if((u.weight<=W) && (u.profit> maxprofit))
                maxprofit = u.profit;
            
            u.bound = bound(u);
            
            printf("%d. 왼 %d depth  %d  %d  %d \n", cnt++, u.level, u.profit, u.weight, bound(u));
            if(u.bound >maxprofit){
                
                enqueue(u);
            }
            //포함안했을때
            u.weight= v.weight;
            u.profit=v.profit;
            u.bound = bound(u);
           printf("%d. 오 %d depth  %d  %d  %d \n", cnt++, u.level, u.profit, u.weight, bound(u));
            if (u.bound > maxprofit){
              
                enqueue(u);
            }
        }
        
    }
}


int main() {
    printf("\n--------------------------------\n");
    printf("Depth first algorithm\n\n");
    knapsack_DFS(0, 0, 0);
    printf("\n최적이 되는 집합\n");
    for(int i = 1; i<=N; i++)
        printf("bestset[%d] : %d\n", i, bestset[i]);
    printf("\nMax Profit:  %d\n", maxprofit);
    printf("\n--------------------------------\n");
    maxprofit =0;
    printf("Breadth first algorithm\n\n");
    knapsack_BFS();
    printf("\nMax Profit:  %d\n", maxprofit);
    printf("\n--------------------------------\n");
    maxprofit =0;
    printf("Best first algorithm\n\n");
    knapsack_BestFS();
    printf("\nMax Profit:  %d\n", maxprofit);
    
    
    
    return 0;
}
