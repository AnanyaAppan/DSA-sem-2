#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int subtract3(int arr[],int n)
{
    if(arr[n-1]>=3) arr[n-1] -= 3;
    else{
        arr[n-1] = arr[n-1]+10 - 3;
        int i=n-2;
        while(arr[i]==0)
        {
            arr[i] = 9;
            i--;
        }
        arr[i]--;
    }
    return 0;
}

int identity(int** x)
{
    for(int i=0;i<3;i++)
    {
        for(int j=0;j<3;j++)
        {
            if(i==j)
            {
                x[i][j] = 1;
            }
            else
            {
                x[i][j] = 0;
            }
        }
    }
    return 0;
}

int matrixMulti(int** a, int** b, int m)
{ 
    int **c = (int **)malloc(3 * sizeof(int *));
    for (int i=0; i<3; i++)
        c[i] = (int *)malloc(3 * sizeof(int));
    for(int i=0;i<3;i++)
        for(int j=0;j<3;j++)
            c[i][j] = 0;
    int i,j,k;
    for(i=0;i<3;i++)
        for(j=0;j<3;j++)
            for(k=0;k<3;k++)
            {
                c[i][j] = (c[i][j]+(a[i][k]* b[k][j])%m)%m;
            }   
    for(int i=0;i<3;i++)
        for(int j=0;j<3;j++)
            a[i][j] = c[i][j];
    for (int i=0; i<3; ++i) {
        free(c[i]);
    }
    free(c);
    return 0;
}

int** p(int **base, int power[], int n, int m)
{
    int **result = (int **)malloc(3 * sizeof(int *));
    for (int i=0; i<3; i++)
         result[i] = (int *)malloc(3 * sizeof(int));
    identity(result);
    int **x = (int **)malloc(3 * sizeof(int *));
    for (int i=0; i<3; i++)
         x[i] = (int *)malloc(3 * sizeof(int));
    for(int i=n-1;i>=0;i--)
    {
        identity(x);
        while(power[i]--)
        {
            matrixMulti(x,base,m);
        }
        matrixMulti(result,x,m);
        int i = 10;
        identity(x);
        while(i--)
        {
            matrixMulti(x,base,m);
        }
        for(int r=0;r<3;r++)
            for(int c=0;c<3;c++)
                base[r][c] = x[r][c];
    }
    for (int i=0; i<3; ++i) {
        free(x[i]);
    }
    free(x);
    return result;
}

int series(int n[],int length,int m)
{
    int **A = (int **)malloc(3 * sizeof(int *));
    for (int i=0; i<3; i++)
         A[i] = (int *)malloc(3 * sizeof(int));
    A[0][0] = 1;
    A[0][1] = 1;
    A[0][2] = 0;
    A[1][0] = 1;
    A[1][1] = 0;
    A[1][2] = 0;
    A[2][0] = 0;
    A[2][1] = 1;
    A[2][2] = 0;
    int **powerMatrix = (int **)malloc(3 * sizeof(int *));
    for (int i=0; i<3; i++)
        powerMatrix[i] = (int *)malloc(3 * sizeof(int));
    powerMatrix = p(A,n,length,m);
    int num1 = 2*powerMatrix[0][0];
    int num2 = powerMatrix[0][1];
    for (int i=0; i<3; ++i) {
        free(powerMatrix[i]);
    }
    free(powerMatrix);
    for (int i=0; i<3; ++i) {
        free(A[i]);
    }
    free(A);
    return num1 + num2;
}

int main()
{
    char* n = (char*)malloc(100000*sizeof(char));
    printf("enter a number\n");
    scanf("%s",n);
    int num[100000],i,m;
    printf("enter modulo\n");
    scanf("%d",&m);
    for(i=0;i<strlen(n);i++)
    {
        num[i] = n[i] - '0';
    }
    if(i==1)
    {
        if(num[0]==0 || num[0]==1 || num[0]==2) 
        {
            printf("the nth number of the series is %d\n",num[0]);
            return 0;
        }
    }
    free(n);
    subtract3(num,i);
    printf("the nth number of the series is %d\n",series(num,i,m));
    return 0;
}