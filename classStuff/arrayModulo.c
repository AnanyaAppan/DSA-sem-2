#include<stdio.h>
#include<stdlib.h>
#include<string.h>

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
        printf("num = %d\n",num);
        arr[i] = num%divisor;
    }
    return num/10;
}

int main()
{
    printf("enter a big number\n");
    int arr[1000000];
    char* s = (char*)malloc(1000000*sizeof(char));
    scanf("%s",s);
    int digits = strlen(s);
    for(int i=0;i<digits;i++)
    {
        arr[i] = s[i]-'0';
    }
    for(int i=0;i<digits;i++) printf("%d ",arr[i]);
    printf("\n"); 
    free(s);
    int divisor;
    printf("enter the divisor\n");
    scanf("%d",&divisor);
    int modulo = findMod(arr,digits,divisor);
    printf("the remainder = %d\n",modulo);
    return 0;
}