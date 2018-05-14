#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>

int printAray(int arr[],int n)
{
    for(int i=0;i<n;i++) printf("%d ",arr[i]);
    printf("\n");
    return 0;
}

int findMod(int arr[],int digits, int divisor)
{
    int i=0,num;
    while(i<digits)
    {
        num = arr[i];
        while(num<divisor && i<digits)
        {
            i++;
            num = num*10 + arr[i];
        }
        arr[i] = num%divisor;
    }
    return num/10;
}

int findFib(int n[],int m,int len)
{
    if((n[0]==0 || n[0]==1) && len==1) return n[0];
    int fib0 = 0;
    int fib1 = 1;
    int result[6*m];
    result[0] = 0;
    result[1] = 1;
    int k = 2;
    int i=0;
    int count=0;
    int period = -1;
    while(i<len)
    {
        int val = n[i]*(pow(10,i));
        while(val>=0)
        {
            result[k]= (fib0 + fib1)%m;
            fib0 = fib1;
            fib1 = result[k];
            val--;
            count++;
            k++;
            if(fib0 == 0 && fib1==1 && period==-1)
            {
                period = count;
                break;
            }
        }
        i++;
        if(period!=-1) 
        {
            return result[findMod(n,len,period)]; 
        }
    }
    if(len==1) return result[count-2];
    return result[count-3];
}



int main()
{
    int n[100000] ,m;
    printf("enter modulo number\n");
    scanf("%d",&m);
    printf("enter the index of fibo number u want\n");
    char* s = (char*)malloc(100000*sizeof(char));
    scanf("%s",s);
    int len = strlen(s);
    for(int i=0;i<len;i++)
    {
        n[i] = s[i]-'0';
    }
    free(s);
    int result = findFib(n,m,len);
    printf("%d\n",result);
    return 0;
}