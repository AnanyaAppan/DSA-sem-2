#include<stdio.h>
#include<stdlib.h>
#define N 30

int enqueue(int queue[],int num,int* front,int* end)
{
    if(*end==N)
    {
        printf("queue full!!\n");
        return 0;
    }
    if(*front==-1)
    {
        *front=0;
    }
    queue[++(*end)]=num;
    return 0;
}

int dequeue(int queue[],int* front,int* end)
{
    if(*front==-1)
    {
        printf("queue empty!!\n");
        return 0;
    }
    int num = queue[*front];
    if(*front==*end)
    {
        *front = -1;
        *end = -1;
    }
    else
    {
        (*front)++;
    }
    return num;
}

int printQueue(int queue[],int* front,int* end)
{
    for(int i=*front;i<=*end;i++)
    {
        printf("%d ",queue[i]);
    }
    printf("\n");
    return 0;
}

int main()
{
    int count = 0,queue[100],k,n,front=-1,end=-1,subSums[100],j=0;
    scanf("%d %d",&n,&k);
    int sum = 0;
    for(int i=0;i<n;i++) 
    {
        int num;
        scanf("%d",&num);
        sum += num;
        printf("sum = %d\n",sum);
        enqueue(queue,num,&front,&end);
        count++;
        if(count>=k)
        {
            int n = dequeue(queue,&front,&end);
            subSums[j] = sum;
            sum -= n;
            j++;
        }
    }
    for(int i=0;i<j;i++) printf("%d ",subSums[i]);
    printf("\n");
    return 0;
}