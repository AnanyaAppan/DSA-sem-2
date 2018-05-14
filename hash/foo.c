#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int strrev(char* rev,char* s)
{
    int len = strlen(s);
    for(int i = len-1;i>=0;i--) rev[i] = s[len-i-1];
    return 0;
}

int main()
{
    char s[20];
    scanf("%s",s);
    char s1[20];
    strrev(s1,s);
    printf("%s %s\n",s,s1);
    return 0;
}