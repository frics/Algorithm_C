#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct nodetype{
    char key[10];
    struct nodetype* left;
    struct nodetype* right;
} nodetype;

typedef nodetype* node_pointer;

float sum(int i, int j, const float P[]){
    float total = 0.0;
    for(int k =i; k<=j; k++)
        total += P[i];
    return total;
}

void optsearchtree(int n, const float P[], float minavg, int R[][7]){
    int i, j, k, diagonal;
    float A[8][7];
    float min;
    
    for(i=1; i<=n; i++){
        A[i][i-1] = 0;
        A[i][i] = P[i];
        
        
        R[i][i] = i;
        R[i][i-1] = 0;
    }
    A[n+1][n] = 0;
    R[n+1][n] = 0;
    for(diagonal = 1; diagonal <= n-1; diagonal++)
        for(i=1; i<= n-diagonal; i++){
            j = i+diagonal;
            min = A[i][i-1] + A[i+1][j] + sum(i,j,P);
            for(k = i; k<=j; k++){
                if(min >= A[i][k-1] + A[k+1][j] + sum(i,j,P)){
                    min = A[i][k-1] + A[k+1][j] + sum(i,j,P);
                    R[i][j] =k;
                }
            }
        }
    minavg = A[1][n];
}

nodetype* tree(int i, int j, int R[][7], char key[][10]){
    int k;
    node_pointer p = malloc(sizeof(node_pointer));
    k = R[i][j];
    if(k ==0)
        return NULL;
    else{
        strcpy(p->key, key[k]);
        p -> left = tree(i, k-1, R, key);
        p -> right  = tree(k+1, j, R, key);
        return p;
    }
}
int main(){
    const float P[7] = {0, 0.05, 0.15, 0.05, 0.35, 0.05, 0.35 };
    float minavg = 0.0;
    int R[8][7] = {0,};
    char key[7][10] = {"", "CASE", "ELSE", "END", "IF", "OF", "THEN"};
    
    optsearchtree(7, P, minavg, R);
    tree(1, 6, R, key);
    
    
    printf("%f", minavg);
}

























/*

int *make_d(int n)  // d배열생성
{
    int i;
    int *d;
    
    d = (int*)malloc(sizeof(int)*(n + 1));  // n크기만큼동적할당
    
    for (i = 0; i <= n; i++)
        {
        printf("input d[%d] : ", i);  // d배열의인자를받음
        scanf("%d", &d[i]);
        }
    return d;
}

int **make_arr(int n)  //2차원배열생성
{
    int i;
    int **Arr;
    
    Arr= (int**)malloc(sizeof(int*) * n);  //2차원배열동적할당
    for (i = 0; i < n; i++)
        Arr[i] = (int*)malloc(sizeof(int)*n);
    return Arr;
}

*/
