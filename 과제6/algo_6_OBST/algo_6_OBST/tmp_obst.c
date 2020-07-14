//
//  main.c
//  algo_6_OBST
//
//  Created by James Choi on 12/10/2019.
//  Copyright © 2019 James Choi. All rights reserved.
//

#include <stdio.h>
#include <string.h>

#define MAX      100      //  최대 아이템의 수

// 아이템을저장할구조체
typedef struct {
    char  key[10];
    float  p;
} element;

// 트리를만들때노드를구성할구조체
typedef struct _nodetype {
    char key[10];
    struct _nodetype *left;
    struct _nodetype *right;
}nodetype;

// 노드구조체포인터
typedef nodetype* node_pointer;

float minimum(float a[MAX + 2][MAX + 1], int i, int j, int *k);      // 가장적은값을리턴하는함수
float sigma(int i, int j);            // m=i ~ m=j 까지합을구하여값을리턴하는함수
node_pointer tree_node(int i, int j);      // 최적이진트리를구축하는함수

int  n;                  // 아이템의개수
element key[MAX + 1];            // 입력받을키구조체
int r[MAX + 2][MAX + 1];            // 배열R이저장될 배열
node_pointer node_root;      // 트리의루트를가리키는구조체포인터변수
float minavg;            //  최소 평균 검색 시간을 저장할 변수

// 최적이진트리검색함수
void search()
{
    int found;
    int result_compare;
    char search_word[10];
    node_pointer p;
    
    // 검색할키를입력받음
    printf("Input Search Key :");
    scanf("%s", search_word);
    
    //  루트 노드의 포인터 복사
    p = node_root;
    
    found = 0;
    while (1) {
        //  key  가 NULL  이면 while  종료 (찾지 못한 경우)
        if (p->key == NULL)
            break;
            
            //  검색 할 키와 저장된 키 비교
            result_compare = strcmp(search_word, p->key);
        
        //  일치 하면 found=1  저장 후 while  문 종료
        if (result_compare == 0) {
            found = 1;
            break;
        }
        else  if (result_compare  <  0)
            p = p->left;                                //  왼쪽 트리 검색
        else
            p = p->right;                                //  오른쪽 트리 검색
    }
    
    
    if (found)
        printf("Found  : %s\n", p->key);                                //  찾았을 때 출력
    else
        printf("Not found\n");   //  찾지 못했을 때 출력
}

//  최적 이진 트리 구축을 시작하는 함수
void  make_tree()
{
    node_root = tree_node(1, n);                //  root  노드의 포인터 저장
}

//  최적 이진 탐색 트리 구축 하는 함수 (재귀 호출)
node_pointer  tree_node(int  i, int  j)
{
    int  k;
    node_pointer  a;
    
    a = (node_pointer)malloc(sizeof(node_pointer));
    
    k = r[i][j];
    if (k == 0)
        return  NULL;
        else {
            strcpy(a->key, key[k].key);                                //  key  값을 노드로 복사
            a->left = tree_node(i, k - 1);                                //  왼쪽 서브 트리 구축
            a->right = tree_node(k + 1, j);                //  오른쪽 서브 트리 구축
            
            return  a;                                //  노드의 포인터 반환
        }
}

//  배열 R  출력
void  print_r()
{
    int  i, j;
    
    printf("\n배열 R  출력\n");
    for (i = 1; i <= n + 1; i++) {
        for (j = 0; j <= n; j++) {
            printf("[%2d ]\t", r[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}


//  i  <=  k  <=  j  일때 a[i][k-1]  +  a[k+1][j]  값 중 최소값 반환
float  minimum(float  a[MAX + 2][MAX + 1], int  i, int  j, int  *k)
{
    int  tmp_k;
    float  tmp_value;
    float  tmp_value2;
    
    tmp_k = i;
    
    //  k=i  일때 계산
    tmp_value2 = a[i][tmp_k - 1] + a[tmp_k + 1][j];
    *k = tmp_k;
    
    for (tmp_k = i + 1; tmp_k <= j; tmp_k++) {
        tmp_value = a[i][tmp_k - 1] + a[tmp_k + 1][j];
        if (tmp_value  <  tmp_value2) {                                //  최소값인지 검사후 최소값 저장
            tmp_value2 = tmp_value;
            *k = tmp_k;                                                                                                                //  최소값일때의 k  값 저장
        }
    }
    return  tmp_value2;
}

//  m=i  에서 m=j  까지의 Pm  의 합 구하여 반환
float sum(int i, int j){
    float  tmp;
    int  m;
    
    tmp = 0;
    for (m = i; m <= j; m++)
        tmp += key[m].p;
    
    return  tmp;
}

//  키와 각 키에 할당될 확률 입력 받음
void init_element()
{
    int  i, j;
    
    printf("아이템의 개수를 입력하시오 : ");
    scanf("%d", &n);
    
    for (i = 1; i <= n; i++) {
        printf("키 입력 (%d)  >>  ", i);
        scanf("%s",key[i].key);
        printf("확률 입력 (%d)  >>  ",i);
        scanf("%f", &key[i].p);
    }
    
    //  배열 r  의 값을 초기화 (가비지 값 없애기 위함)
    for (i = 0; i <= n + 1; i++)
        for (j = 0; j <= n; j++)
            r[i][j] = 0;
}

           //  최적 이진 검색 트리 구축을 위한 r  배열 구성
void  optsearchtree()
{
    int  i, j, k, diagonal;
    float  a[MAX + 2][MAX + 1] ={0,};
    
    //  a  배열과 r  배열에 초기값 입력
    for (i = 1; i <= n; i++) {
        a[i][i - 1] = 0;
        a[i][i] = key[i].p;
        r[i][i] = i;
        r[i][i - 1] = 0;
    }
    
    a[n + 1][n] = 0;
    r[n + 1][n] = 0;
    
    for (diagonal = 1; diagonal <= n - 1; diagonal++)
        for (i = 1; i <= n - diagonal; i++) {
            j = i + diagonal;
            a[i][j] = minimum(a, i, j, &k) + sum(i, j);             //  일반식 구현
            r[i][j] = k;                          //  최소 값을 주는 k  값 저장
        }
    minavg = a[1][n];
    printf("\n배열 A  출력\n");
    for (i = 1; i <= n ; i++) {
        for (j = 0; j <= n; j++) {
            printf("[%.2lf]\t", a[i][j]);
        }
        printf("\n");
    }
    
}
           
           // 메인
int  main(void)
{
    init_element();      // 초기화
    optsearchtree();      // a배열과 r배열구성
    print_r();      // r배열출력
    printf("최소 평균 검색 시간 : %f\n\n",minavg);      // 최소평균검색시간출력
    make_tree();      // 최적이진탐색트리구축
    search();      // 검색
}

