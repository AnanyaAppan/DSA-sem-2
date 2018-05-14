#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

int hash(char* x, int len)
{
    int p = 100003;
    int result = 0;
    for(int i=0;i<len;i++)
    {
        result = (result%p+((int)x[i]*(int)pow(26,len-i-1))%p)%p;
    }
    return result;
}

int RobinKarp(char* string, char* substr)
{
    int len1 = strlen(substr);
    int len2 = strlen(string);
    int hash1 = hash(substr,len1);
    char* firstStr = (char*)malloc(len1*sizeof(char));
    for(int i=0;i<len1;i++) 
    {
        firstStr[i] = string[i];
    }
    firstStr[len1] = '\0';
    int hash2 = hash(firstStr,len1);
    int count = 0;
    int p = 100003;
    //printf("hashval = %d\n",hash1);
    //printf("hashval = %d\n",hash2);
    if(hash1 == hash2) count++;
    for(int i=1; i<=len2-len1;i++)
    {
        //printf("str[i-1] = %c, str[i+1] = %c\n",string[i-1],string[i+1]);
        hash2 = (hash2 * (26%p))%p;
        hash2 = (hash2-(((int)string[i-1])*(int)pow(26,len1))%p)%p;
        //printf("hashval(after subtracting) = %d\n",hash2);
        if(hash2<0) hash2 += p;
        //printf("hashval = %d\n",hash2);
        hash2 = (hash2 + ((int)string[i+len1-1])%p)%p;
        //printf("hashval (after adding)= %d\n",hash2);
        if(hash2 == hash1)
        {
            int flag = 1;
            for(int j=i,k=0;j<len1+i;j++,k++)
            {
                if(string[j]!=substr[k])
                {
                    flag = 0;
                    break;
                }
            }
            if(flag) count++;
        }
    }
    return count;
}

int main()
{
    printf("enter main string\n");
    char* string = (char*)malloc(100000*sizeof(char));
    scanf("%s",string);
    printf("enter sub string\n");
    char* substr = (char*)malloc(100000*sizeof(char)); 
    scanf("%s",substr); 
    int count;
    count = RobinKarp(string,substr);
    printf("number of times substring repeats = %d\n",count);
    free(string);
    free(substr);
    return 0;
}