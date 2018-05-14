#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#define p 101
#define D 100
//char s[10][10000];
int arr[100][102];
int pos[102][3];

int stringhash(char* x, int len)
{
    int result = 0;
    for(int i=0;i<len;i++)
    {
        result = (result%p+(x[i]*(int)pow(D,len-i-1))%p)%p;
    }
    
    return result;
}

int common(int* Hash,char** s,int len,int n,int k,int l)
{
    for(int i=0;i<k;i++)
        for(int j=0;j<102;j++)
            arr[i][j] = 0;
    for(int p1=0;p1<k;p1++)
    {
        printf("string = %s\n",s[p1]);
        if(strlen(s[p1])>len)
        {
            char* firstStr = (char*)malloc(len*sizeof(char));
            for(int i=0;i<len;i++) 
            {
                firstStr[i] = s[p1][i];
            }
            firstStr[len] = '\0';
            int hash = stringhash(firstStr,len);
            arr[p1][hash] = 1;
            pos[hash][0] = 0;
            pos[hash][1] = len-1;
            pos[hash][2] = p1;
            for(int i=1; i<=strlen(s[p1])-len;i++)
            {
                hash = (hash * (D%p))%p;
                hash = (hash-((s[p1][i-1])*(int)pow(D,len))%p)%p;
                if(hash<0) hash += p;
                hash = (hash + (s[p1][i+len-1])%p)%p;
                arr[p1][hash] = 1;
                pos[hash][0] = i;
                pos[hash][1] = i+len-1;
                pos[hash][2] = p1;
                //printf("%d %d\n",p1,hash);
            }
        }
    }
    for(int c=0;c<p;c++)
    {
        int count = 0;
        for(int r=0;r<k;r++)
        {
            if(arr[r][c]) count++;
            if(count>=l)
            {
                *Hash = c;
                return 1;
            }
        }
    }
    return 0;
}

int findBiggest(char** s,int n,int k,int l,int len)
{
    // for(int i=0;i<k;i++)
    // {
    //     printf("%s",s[k]);
    //     //if(strlen(s[k])>len) len = strlen(s[k]);
    // }
    int hash = 0;
    int beg = 0, end = len;
    int ans = 0;
    while(beg<=end)
    {
        int mid = (beg+end)/2;
        printf("len = %d\n",mid);
        if(common(&hash,s,mid,n,k,l))
        {
            beg = mid+1;
            ans = mid;
        }
        else
        {
            end = mid-1;
        }
    }
    // printf("the string is..\n");
    // for(int i=pos[hash][0];i<=pos[hash][1];i++)
    // {
    //     printf("%c",s[pos[hash][2]][i]);
    // }
    // printf("\n");
    return ans;
}

int main()
{
    int n,k,l;
    char** s = (char**)malloc(100*sizeof(char*));
    for(int i=0;i<100;i++)
    {
        s[i] = (char*)malloc(10000*sizeof(char));
    }
    scanf("%d %d %d",&n,&k,&l);
    int len = 0;
    for(int i=0;i<k;i++)
    {
        scanf("%s",s[i]);
        if(strlen(s[i])>len) len = strlen(s[i]);
    }
    int ans = findBiggest(s,n,k,l,len);
    printf("%d\n",ans);
    return 0;
}