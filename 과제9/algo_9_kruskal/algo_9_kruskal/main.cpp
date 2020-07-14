#include <stdio.h>

#define TRUE 1
#define FALSE 0
#define MAX_NODE 10
#define INF 987654321
#define MAX_ELEMENT 13 // 히프의 최대크기


int parent[MAX_NODE]; // 각 정점의 부모 노드
int num[MAX_NODE];    // 각 집합의 크기

typedef struct{
    int distance;  // 간선의 가중치
    int p;    // 정점 1
    int q;    // 정점 2
} element;

typedef struct{
    element heap[MAX_ELEMENT];
    int heap_size;
} HeapType;

void init(int n){// 노드 초기화
    
    int i;
    for (i = 0; i < n; i++){
        parent[i] = -1;
        num[i] = 1;
    }
}

int find(int vertex){ // 같은 부모를 가지는지 확인하는 함수
    int p, s, i = -1; // p: 부모노드
    for (i = vertex; (p = parent[i]) >= 0; i = p);
    
    s = i;  // 루트노드 정보를 s에 저장
    
    for (i = vertex; (p = parent[i]) >= 0; i = p)
        parent[i] = s; //부모노들이 s로 가게 한다
    
    return s; // 루트 노드 반환
}


void merge(int p, int q){
    if (num[p] < num[q]){ //더 큰쪽으로 부모노드를 합침
        parent[p] = q;
        num[p] += num[q];
    }
    else{
        parent[q] = p;
        num[p] += num[q];
    }
}

void init_heap(HeapType *h){
    h->heap_size = 0;
}

void insert_min_heap(HeapType *h, element item){
    int i = ++(h->heap_size);
    while ((i != 1) && (item.distance < h->heap[i / 2].distance)){
        h->heap[i] = h->heap[i / 2];
        i /= 2;
    }
    h->heap[i] = item;
}

element delete_min_heap(HeapType *h){
    int parent, child;
    element item, temp;
    
    item = h->heap[1];
    
    temp = h->heap[(h->heap_size)--];
    
    parent = 1;
    child = 2;
    
    while (child <= h->heap_size){
        if ((child < h->heap_size) && (h->heap[child].distance) > h->heap[child + 1].distance)
            child++;
        if (temp.distance <= h->heap[child].distance)
            break;
        
        h->heap[parent] = h->heap[child];
        parent = child;
        child *= 2;
    }
    h->heap[parent] = temp;
    return item;
}

void insert_heap_edge(HeapType *h, int p, int q, int weight){
    element e;
    e.p = p;
    e.q = q;
    e.distance = weight;
    insert_min_heap(h, e);
}

void insert_all_edges(HeapType *h){
    insert_heap_edge(h, 3, 7, 3);
    insert_heap_edge(h, 7, 8, 4);
    insert_heap_edge(h, 2, 6, 5);
    insert_heap_edge(h, 5, 9, 6);
    insert_heap_edge(h, 3, 4, 10);
    insert_heap_edge(h, 8, 9, 12);
    insert_heap_edge(h, 0, 3, 17);
    insert_heap_edge(h, 2, 3, 18);
    insert_heap_edge(h, 4, 7, 28);
    insert_heap_edge(h, 0, 1, 32);
    insert_heap_edge(h, 1, 4, 45);
    insert_heap_edge(h, 6, 7, 59);
}

void kruskal(HeapType h){
    int edge_accepted = 0;  // 현재까지 연결된 간선 수
    int p, q;  // 서로 연결되있는 2노드
    int sum = 0;
    element e;
    
    
    init(MAX_NODE);  // 부분집합 초기화
    
    while (edge_accepted < (MAX_NODE - 1)){ // 간선의 수 < (n - 1)
        e = delete_min_heap(&h);
        p = find(e.p);
        q = find(e.q);
        
        // 두 집합이 서로 다른 집합에 속한다면
        if (p != q){
            printf("V%d, V%d 연결 weight : %2d \n", e.p+1, e.q+1, e.distance);
            edge_accepted++;
            sum+= e.distance;
            merge(p, q);  // 두 개의 집합을 합친다.
            }
        }
    printf("MST by kruskal algorithm : %d\n", sum);
}

int main()
{
    HeapType h;
    init_heap(&h);
    insert_all_edges(&h);
    kruskal(h);
    
}

