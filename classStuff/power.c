#include<stdio.h>
#include<stdlib.h>
#include<string.h>
# define N 1000

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

int main()
{
    long long int base;
    char exponent[N];
    printf("enter base and power\n");
    scanf("%lld",&base);
    scanf("%s",exponent);
    int power[N];
    int i;
    for(i = 0;i<strlen(exponent);i++ )
    {
        power[i] = exponent[i]-'0';
    }
    printf("the power is %ld\n",p(base,power,i));
    return 0;
}