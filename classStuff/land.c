#include<stdlib.h>
#include<stdio.h>

// int assign(int** arr,int size)
// {
//     arr = (int**)malloc(size*sizeof(int*));
//     for(int i=0;i<size;i++)
//     {
//         arr[i] = (int*)malloc(size*sizeof(int));
//     }
//     return 0;
// }

int Free(int** arr, int size)
{
    for(int i=0;i<size;i++)
    {
        free(arr[i]);
    }
    free(arr);
    return 0;
}

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

int* nextNumRight(int arr[], int n,int arr2[])
{
    int stack[100],top = -1;
    int* res;
    res = (int *) malloc(n*sizeof(int));
    res[n-1] = -1;
    push(stack,n-1,&top);
    for(int i = n-2;i>=0;i--)
    {
        if(arr2[i+1]!=0)
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
        else{
            res[i] = i+1;
        }
    }
    return res;
}

int* nextNumLeft(int arr[], int n,int arr2[])
{
    int stack[100],top = -1;
    int* res;
    res = (int *) malloc(n*sizeof(int));
    res[0] = -1;
    push(stack,0,&top);
    for(int i = 1;i<n;i++)
    {
        if(arr2[i-1]!=0)
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
        else{
            res[i] = i-1;
        }
    }
    return res;
}

int histogram(int arr[],int n,int arr2[])
{
    int maxArea = 0;
    int* minLeft = (int*)malloc(n*sizeof(int));
    int* minRight = (int*)malloc(n*sizeof(int));
    minLeft = nextNumLeft(arr,n,arr2);
    minRight = nextNumRight(arr,n,arr2);
    for(int i=0;i<n;i++)
    {
        if(arr2[i]!=0)
        {
            int right,left;
            int height = arr[i];
            if(minLeft[i]!=-1) left = i - minLeft[i] - 1;
            else left = i;
            if(minRight[i]!=-1) right = minRight[i] - i -1;
            else right = n-1-i;
            //printf("left = %d right = %d\n",left,right);
            int area = height*(left+right+1);
            if(area>maxArea) maxArea = area;
        } 
    }
    free(minLeft);
    free(minRight);
    return maxArea;
}

int findLargestLand(int** arr,int n)
{
    int** prefixSum;
    prefixSum = (int**)malloc(n*sizeof(int*));
    for(int i=0;i<n;i++) prefixSum[i] = (int*)malloc(n*sizeof(int));
    //calculating the heights....
    prefixSum[0][0] = arr[0][0];
    for(int j=1;j<n;j++)
    {
        prefixSum[0][j] = prefixSum[0][j-1]+arr[0][j];
    }
    for(int i=1;i<n;i++)
    {
        prefixSum[i][0] = prefixSum[i-1][0]+arr[i][0];
    }
    for(int i=1;i<n;i++)
    {
        for(int j=1;j<n;j++)
        {
            prefixSum[i][j] = prefixSum[i-1][j]+prefixSum[i][j-1]-prefixSum[i-1][j-1]+arr[i][j];
        }
    }
    int** heights;
    heights =(int**)malloc(n*sizeof(int*));
    for(int i=0;i<n;i++) heights[i] = (int*)malloc(n*sizeof(int));
    for(int i=0;i<n;i++)
    {
        heights[i][0] = prefixSum[i][0];
    }
    for(int i=1;i<n;i++)
    {
        for(int j=1;j<n;j++)
        {
            heights[i][j] = prefixSum[i][j] - prefixSum[i][j-1];
        }
    }
    for(int j=1;j<n;j++)
    {
        heights[0][j] = prefixSum[0][j] - prefixSum[0][j-1];
    }
    int maxArea = 0;
    for(int i=0;i<n;i++)
    {
        int area = histogram(heights[i],n,arr[i]);
        if(area>maxArea) maxArea = area;
    }
    for(int i=0;i<n;i++)
    {
        free(heights[i]);
        free(prefixSum[i]);
    }
    free(heights);
    free(prefixSum);
    return maxArea;
}


int main()
{
    int n;
    int** arr;
    printf("enter side of the square\n");
    scanf("%d",&n);
    arr = (int**)malloc(n*sizeof(int*));
    for(int i=0;i<n;i++)
    {
        arr[i] = (int*)malloc(n*sizeof(int));
    }
    printf("enter the matrix\n");
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {          
            scanf("%d",&arr[i][j]);
        }
    }
    int result = findLargestLand(arr,n);
    printf("largest land available = %d\n",result);
    Free(arr,n);
    return 0;
}