#include<stdio.h>
#include<stdlib.h>

int enqueue(int queue[],int num,int* front,int* end)
{
    if(*front==-1)
    {
        *front=0;
    }
    queue[++(*end)]=num;
    return 0;
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
    int queue[30];
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
    return 0;
}