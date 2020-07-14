#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define N 100

LARGE_INTEGER Frequency;
LARGE_INTEGER BeginTime;
LARGE_INTEGER Endtime;

void merge_sort(double a[],int i,int j);
void merge(double a[],int i1,int j1,int i2,int j2);
void quick_sort(double[],int,int);
int partition(double[],int,int);

void exchange_sort(double list[], int n){
    int i, j;
    double tmp;
    for(i = 0; i < (n -1); i++)
    {
        for (j=(i + 1); j < n; j++)
        {
            if (list[i] > list[j])
            {
                tmp = list[i];
                list[i] = list[j];
                list[j] = tmp;
            }
        }
    }
}
void insertion_sort(double list[], int n){
    int i, j;
    double key;
    
    // 인텍스 0은 이미 정렬된 것으로 볼 수 있다.
    for(i=1; i<n; i++){
        key = list[i]; // 현재 삽입될 숫자인 i번째 정수를 key 변수로 복사
        
        // 현재 정렬된 배열은 i-1까지이므로 i-1번째부터 역순으로 조사한다.
        // j 값은 음수가 아니어야 되고
        // key 값보다 정렬된 배열에 있는 값이 크면 j번째를 j+1번째로 이동
        for(j=i-1; j>=0 && list[j]>key; j--){
            list[j+1] = list[j]; // 레코드의 오른쪽으로 이동
        }
        
        list[j+1] = key;
    }
}

void merge_sort(double a[],int i,int j)
{
    int mid;
        
    if(i<j)
    {
        mid=(i+j)/2;
        merge_sort(a,i,mid);        //left recursion
        merge_sort(a,mid+1,j);    //right recursion
        merge(a,i,mid,mid+1,j);    //merging of two sorted sub-arrays
    }
}
 
void merge(double a[],int i1,int j1,int i2,int j2)
{
    double temp[50];    //array used for merging
    int i,j,k;
    i=i1;    //beginning of the first list
    j=i2;    //beginning of the second list
    k=0;
    
    while(i<=j1 && j<=j2)    //while elements in both lists
    {
        if(a[i]<a[j])
            temp[k++]=a[i++];
        else
            temp[k++]=a[j++];
    }
    
    while(i<=j1)    //copy remaining elements of the first list
        temp[k++]=a[i++];
        
    while(j<=j2)    //copy remaining elements of the second list
        temp[k++]=a[j++];
        
    //Transfer elements from temp[] back to a[]
    for(i=i1,j=0;i<=j2;i++,j++)
        a[i]=temp[j];
}
void quick_sort(double a[],int low,int high)
{
    int j;
    if(low<high)
    {
        j = partition(a,low,high);
        quick_sort(a,low,j-1);
        quick_sort(a,j+1,high);
    }
}
 
int partition(double a[],int low,int high)
{
    int i,j;
    double v, temp;
    v=a[low];
    i=low;
    j=high+1;
    
    do
    {
        do
            i++;
            
        while(a[i]<v&&i<=high);
        
        do
            j--;
        while(v<a[j]);
        
        if(i<j)
        {
            temp=a[i];
            a[i]=a[j];
            a[j]=temp;
        }
    }while(i<j);
    
    a[low]=a[j];
    a[j]=v;
    
    return(j);
}


float randomRange() {
    return (2*((double)rand()/RAND_MAX))-1;
}

int main(void){
    int i;
    double ary[N], time;
    
    srand((unsigned)time(NULL));
    printf("정렬전");
    for (i = 0; i < N; i++){
        ary[i] = randomRange();
        printf("%.3lf \t", ary[i]);
    }
  //  QueryPerformanceFrequency(&PreFreq);
    QueryPerformanceCounter(&s1)
    quick_sort(ary,0,N-1);
    QueryPerformanceCounter(&s2);                                         //interative함수 수행시간측정을 위한 종단점
    time= (double)(s2.QuadPart - s1.QuadPart)/ (double)PreFreq.QuadPart;  //각각 시작점과 종단점에 의해 얻어진 값의 차이를 구해서 수행시간 판단
    printf("cost time: %f\n", time);
    //merge_sort(ary,0,N-1);
    //exchange_sort(ary,N);
    //insertion_sort(ary,N);
    printf("\n정렬 후");
    for(i=0; i < N; i++){
        printf("%.3lf \t", ary[i]);
    }
    
    return 0;
}
