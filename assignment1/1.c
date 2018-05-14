#include<stdio.h>
#include<stdlib.h>


int push(int arr[],int n,int *top)
{
    if(*top == n)
    {
        printf("stack full\n");
        return 0;
    }
    arr[++(*top)] = n;
    return 0;
}

int pop(int arr[],int *top)
{
    if(*top == -1)
    {
        printf("stack empty\n");
        return 0;
    }
    int num = arr[(*top)--];
    return num;
}

int printStack(int stack[],int* top)
{
    for(int i=0;i<=*top;i++)
    {
        printf("%d ",stack[i]);
    }
    printf("\n");
    return 0;
}

int main()
{
    int q;
    int stack[100];
    int top1 = -1;
    int max[100];
    int top2 = -1;
    scanf("%d",&q);
    while(q--)
    {
        printStack(stack,&top1);
        int choice;
        scanf("%d",&choice);
        if(choice==1)
        {
            int num;
            scanf("%d",&num);
            push(stack,num,&top1);
            if(top2 != -1)
            {
                if(num>max[top2])
                {
                    push(max,num,&top2);
                }
            }
            else{
                push(max,num,&top2);
            }
        }
        else if(choice==2)
        {
            if(stack[top1]==stack[top2])
            {
                pop(max,&top2);
            }
            pop(stack,&top1);
        }
        else{
            printf("the maximum element is %d\n",max[top2]);
        }
        printf("the stack is\n");
    }
}