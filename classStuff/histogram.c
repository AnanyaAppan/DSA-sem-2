#include<stdlib.h>
#include<stdio.h>

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

int* nextNumRight(int arr[], int n)
{
    int stack[100],top = -1;
    int* res;
    res = (int *) malloc(n*sizeof(int));
    res[n-1] = -1;
    push(stack,n-1,&top);
    for(int i = n-2;i>=0;i--)
    {
        if(arr[i]>arr[i+1])
        {
            res[i] = i+1;
            push(stack,i,&top);
        }
        else
        {
            while(top!=-1)
            {
                if(arr[stack[top]]>=arr[i])
                {
                    pop(stack,&top);
                }
                else
                    break;
            }
            push(stack,i,&top);
            if(top==0) res[i] = -1;
            else res[i] = stack[top-1];
        }
    }
    return res;
}

int* nextNumLeft(int arr[], int n)
{
    int stack[100],top = -1;
    int* res;
    res = (int *) malloc(n*sizeof(int));
    res[0] = -1;
    push(stack,0,&top);
    for(int i = 1;i<n;i++)
    {
        if(arr[i]>arr[i-1])
        {
            res[i] = i-1;
            push(stack,i,&top);
        }
        else
        {
            while(top!=-1)
            {
                if(arr[stack[top]]>=arr[i])
                {
                    pop(stack,&top);
                }
                else
                    break;
            }
            push(stack,i,&top);
            if(top==0) res[i] = -1;
            else res[i] = stack[top-1];
        }
    }
    return res;
}

int histogram(int arr[],int n)
{
    int maxArea = 0;
    int* minLeft = (int*)malloc(n*sizeof(int));
    int* minRight = (int*)malloc(n*sizeof(int));
    minLeft = nextNumLeft(arr,n);
    minRight = nextNumRight(arr,n);
    for(int i=0;i<n;i++)
    {
        int right,left;
        int height = arr[i];
        if(minLeft[i]!=-1) left = i - minLeft[i] - 1;
        else left = i;
        if(minRight[i]!=-1) right = minRight[i] - i -1;
        else right = n-1-i;
        printf("left = %d right = %d\n",left,right);
        int area = height*(left+right+1);
        if(area>maxArea) maxArea = area;
    }
    free(minLeft);
    free(minRight);
    return maxArea;
}

int main()
{
    int arr[10000];
    int n;
    scanf("%d",&n);
    for(int i=0;i<n;i++) scanf("%d",&arr[i]);
    int area = histogram(arr,n);
    printf("max area = %d\n",area);
    return 0;
}