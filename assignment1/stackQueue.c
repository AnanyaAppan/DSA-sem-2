#include<stdio.h>
#include<stdlib.h>


typedef struct queue
{
    int pushStack[100], popStack[100];
    int top1;
    int top2;
    int minStackPush[100];
    int top3;
    int top4;
    int minStackPop[100];
}queue;


int push(int arr[],int n,int *top)
{
    arr[++(*top)] = n;
    return 0;
}

int pop(int arr[],int *top)
{
    int num = arr[(*top)--];
    return num;
}

int enqueue(queue** q,int num)
{
    if((*q)->top1==-1)
    {
        push((*q)->minStackPush,num,&((*q)->top3));
    }
    else
    { 
        if((*q)->top3!=-1)
        {
            if(num>(*q)->minStackPush[(*q)->top3])
            {
                push((*q)->minStackPush,num,&((*q)->top3));
            }
            else{
                while(num<(*q)->minStackPush[(*q)->top3])
                {
                    pop((*q)->minStackPush,&((*q)->top3));
                }
                push((*q)->minStackPush,num,&((*q)->top3));
            }
        }
        else{
            if(num>(*q)->minStackPop[0])
            {
                push((*q)->minStackPush,num,&((*q)->top3)); 
            }
        }
    }
    push((*q)->pushStack,num,&((*q)->top1));
    return 0;
}

int dequeue(queue** q)
{
    int num;
    if((*q)->top1==-1 && (*q)->top2==-1)
    {
        printf("the queue is empty\n");
        return -1;
    }
    if((*q)->top2==-1)
    {
        while((*q)->top1!=-1)
        {
            num = pop((*q)->pushStack,&((*q)->top1));
            push((*q)->popStack,num,&((*q)->top2));
        }
    }
    num = pop((*q)->popStack,&((*q)->top2));
    if((*q)->top4 != -1)
    {
        if(num==(*q)->minStackPop[(*q)->top4])
        {
            pop((*q)->minStackPop,&(*q)->top4);
        } 
    }
    else if(num==(*q)->minStackPush[0])
    {
        int n;
        while((*q)->top3!=-1)
        {
            n = pop((*q)->minStackPush,&((*q)->top3));
            push((*q)->minStackPop,n,&((*q)->top4));
        } 
        pop((*q)->minStackPop,&((*q)->top4)); 
    }
    return num;
}

int min(queue* q)
{
    if(q->top4 != -1 && q->top3!=-1)
    {
        int min1 = q->minStackPush[0];
        int min2 = q->minStackPop[q->top4];
        if(min1<min2) return min1;
        else return min2;
    }
    else if(q->top3 != -1)
    {
        return q->minStackPush[0];
    }
    else
    {
        return q->minStackPop[q->top4];
    }
}

int printQueue(queue* q)
{
    for(int i=q->top2;i>=0;i--)
    {
        printf("%d ",q->popStack[i]);   
    }
    for(int i=0;i<=q->top1;i++)
    {
        printf("%d ",q->pushStack[i]);
    }
    printf("\n");
    return 0;
}

int main()
{
    queue* q = (queue *)malloc(sizeof(queue));
    q->top1 = -1;
    q-> top2 = -1;
    q->top3 = -1;
    q->top4 = -1;
    enqueue(&q,1);
    enqueue(&q,2);
    enqueue(&q,3);
    enqueue(&q,4);
    printf("the queue is..\n");
    printQueue(q);
    printf("the queue after dequeuing is...\n");
    dequeue(&q);
    printQueue(q);
    printf("the minimum is %d \n",min(q));
    dequeue(&q);
    dequeue(&q);
    printQueue(q);
    return 0;
}