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
    int queue[N];
    int ans = 1;
    printf("enter 1 to enter a number\n");
    scanf("%d",&ans);
    int start = -1;
    int end = -1;
    while(ans)
    {
        int num;
        printf("enter number\n");
        scanf("%d",&num);
        enqueue(queue,num,&start,&end);
        printf("queue is..\n");
        printQueue(queue,&start,&end);
        printf("enter 1 to enter a number\n");
        scanf("%d",&ans);
    }
    printf("now for dequeue.... >_<\n");
    printf("enter 1 to remove a number\n");
    scanf("%d",&ans);
    while(ans)
    {
        printf("number removed = %d\n",dequeue(queue,&start,&end));
        printQueue(queue,&start,&end);
        printf("enter 1 to remove a number\n");
        scanf("%d",&ans);
    }
    return 0;
}