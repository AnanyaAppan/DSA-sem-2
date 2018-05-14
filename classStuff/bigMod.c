#include<stdio.h>
#include<stdlib.h>
#include<string.h>

long int p(long long int base, int power[], int n)
{
    printf("n = %d\n",n);
    long int result=1;
    for(int i=n-1;i>=0;i--)
    {
        printf("%d \n",power[i]);
        long long int x = 1;
        while(power[i]--)
        {
            x = x*base;
        }
        printf("x=%lld\n",x);
        result = result*x;
        int i = 10;
        x = 1;
        while(i--)
        {
            x = x*base;
        }
        base = x;
        printf("base=%lld\n",base);
        printf("result = %ld\n",result);
    }
    return result;
}

int bigModulo(int n1,int n2, int l1,int l2)
{
    while(n1>n2)
    {
        int subNum;
        subNum = n1/p()
    }
}

int main()
{
    printf("enter two numbers\n");
    int n1,n2;
    scanf("%d",n1);
    scanf("%d",n2);
    int l1,l2;
    l1 = strlen(n1+'0');
    l2 = strlen(n2+'0');
    printf("the modulo is %d",bigModulo(n1,n2));
    return 0;
}