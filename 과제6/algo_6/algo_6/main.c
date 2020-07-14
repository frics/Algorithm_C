#include <stdio.h>
#include<stdlib.h>
#include <time.h>

int *make_d(int);
int **make_arr(int);
int minmult(int, const int[], int*[]);
void order(int, int, int*[]);
void print_map(int*[], int);


int main(void)
{
    int i;
    int n = 0, ret;
    int *d, **P;
    

    printf("[Minimum Multiplications algorithm]\n\n");
    printf("Input array number : ");
    scanf("%d", &n);
    
    d = make_d(n);
    P = make_arr(n + 1);
    ret = minmult(n, d, P);
    
    printf("\n  [P]");
    print_map(P, n);
    
    printf("Multiplications order is : ");
    order(1, n, P);
    printf("\nMinimum Multiplications is %d\n", ret);
    
    free(d);
    for (i = 0; i < n; i++)
        free(P[i]);
    free(P);
    
    getchar();
    getchar();
    system("clear");
    return 0;
}

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

int minmult(int n, const int d[], int *P[])  //minimum matrix multiplication
{
    int i, j, k, diagonal;
    int **M, temp = 0, min_k = 0;
    
    M = make_arr(n + 1);
    
    for(i = 1; i <= n; i++)
        M[i][i] = 0;
    
    for (diagonal = 1; diagonal <= n - 1; diagonal++)
        for (i = 1; i <= n - diagonal; i++){
            j = i + diagonal;
            for (k = i; k <= j - 1; k++)
                {
                M[i][j] = M[i][k] + M[k + 1][j] + d[i - 1] * d[k] * d[j];
                
                if (i == k)
                    {
                    temp = M[i][j];
                    min_k = k;
                    }
                else if (M[i][j] > temp)
                    M[i][j] = temp;
                else
                    min_k = k;
                }
            P[i][j] = min_k;                          
            }
    printf("\n  [M]");
    print_map(M, n);
    return M[1][n];
}

void order(int i, int j, int *P[])  // 최적의 순서 출력함수
{
    int k;
    if (i == j)
        printf("A[%d]", i);
    else
        {
        k = P[i][j];
        printf("(");
        order(i, k, P);
        order(k + 1, j, P);
        printf(")");
        }
}

void print_map(int *map[], int n)  //map 출력을위한함수
{
    int i, j, i_cnt = 1, j_cnt = 1;
    
    for (i = 0; i <= n; i++)
        {
        for (j = 0; j <= n; j++)
            {
            printf("  ");
            if (i == 0)
                {
                if (i_cnt == 1)
                    printf(" ");
                if (i_cnt == n + 1)
                    continue;
                printf("[%d] ", i_cnt++);
                }
            else if (j == 0)
                printf("[%d]", j_cnt++);
            else
                if (i < j)
                    printf("%3d ", map[i][j]);
                else if (i >= j && map[i][j] < 0)
                    printf("%3c ", ' ');
                else
                    printf("%3d ", 0);
            }
        printf("\n");
        }
    printf("\n");
}

