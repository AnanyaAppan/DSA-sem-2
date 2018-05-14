#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define prime 101
#define d 10

typedef struct node{
    int data;
    struct node *next;
}node;

int stringhash(char* x, int len)
{
    int p = 100003;
    int result = 0;
    for(int i=0;i<len;i++)
    {
        result = (result%p+((int)x[i]*(int)pow(D,len-i-1))%p)%p;
    }
    return result;
}

int search(struct node *head,int num)
{
    int ans = 0;
    while(head != NULL)
    {
        if(head->data == num)
        {
            return ans;
        }
        head = head->next;
        ans++;
    }
    return -1;
}

int hash(int x)
{
    int p = 101513;
    return x%p;
}

int printList(struct node *head)
{
    while(head != NULL)
    {
        printf("%d\t",head->data);
        head = head->next;
    }
    return 0;
}

int insertBeg(struct node **head, int data)
{
    struct node *temp = (struct node *)malloc(sizeof(struct node));
    temp->next = (*head);
    *head = temp;
    temp->data = data;
    return 0;
}

int delBeg(struct node **head)
{
    if(*head != NULL)
    {   
        struct node *temp = (struct node *)malloc(sizeof(struct node));
        temp = *head;
        *head = (*head)->next;
        free(temp);
        return 0;
    }
}

int delPos(struct node **head, int pos)
{
    if(head != NULL)
    {
        if(pos == 1)
        {
            delBeg(head);
            return 0;
        }
        struct node *temp = (struct node *)malloc(sizeof(struct node));
        struct node *temp2 = (struct node *)malloc(sizeof(struct node));
        temp = *head;
        int cur = 1;
        while(cur != pos)
        {
            temp2 = temp;
            temp = temp->next;
            cur++;
        }
        temp2->next = temp->next;
        free(temp);
        return 0;
    }
    return 1;
}

int add(int x, node* arr[])
{
    int pos = hash(x);
    insertBeg(&arr[pos],x);
    return 0;
}

int del(int x, node* arr[])
{
    int pos1 = hash(x);
    int pos2 = search(arr[pos1],x);
    delPos(&arr[pos1],pos2+1);
    return 0; 
}

int HashTableSearch(int x,node* arr[])
{
    int pos = hash(x);
    if(search(arr[pos],x)!=-1) return 1;
    return 0;
}

int findHash(char* string, int len, node* arr[])
{
    char* firstStr = (char*)malloc(len*sizeof(char));
    int p = 100003;
    for(int i=0;i<len;i++) 
    {
        firstStr[i] = string[i];
    }
    firstStr[len] = '\0';
    int hash = stringhash(firstStr,len);
    add(hash,arr);
    printf("hash added = %d\n",hash);
    for(int i=1; i<=strlen(string)-len;i++)
    {
        hash = (hash * (D%p))%p;
        hash = (hash-(((int)string[i-1])*(int)pow(D,len))%p)%p;
        if(hash<0) hash += p;
        hash = (hash + ((int)string[i+len-1])%p)%p;
        add(hash,arr);
        printf("hash added = %d\n",hash);
    }
    return 0;
}

int searchHash(char* string, int len, node* arr[])
{
    char* firstStr = (char*)malloc(len*sizeof(char));
    for(int i=0;i<len;i++) 
    {
        firstStr[i] = string[i];
    }
    firstStr[len] = '\0';
    int hash = stringhash(firstStr,len);
    if(HashTableSearch(hash,arr)) return 1;
    printf("hash found = %d\n",hash);
    int p = 100003;
    for(int i=1; i<=strlen(string)-len;i++)
    {
        hash = (hash * (D%p))%p;
        hash = (hash-(((int)string[i-1])*(int)pow(D,len))%p)%p;
        if(hash<0) hash += p;
        hash = (hash + ((int)string[i+len-1])%p)%p;
        if(HashTableSearch(hash,arr)) return 1;
        printf("hash found = %d\n",hash);
    }
    return 0;
}

int longestCommonSubstr(char* s1, char* s2)
{
    node* arr[101513];
    int l1 = strlen(s1);
    int l2 = strlen(s2);
    int lmin,lmax;
    int ans = 0;
    char* substr = (char*)malloc(lmin*sizeof(char));
    if(l1>l2)
    {
        lmin = l2;
        lmax = l1;
    }
    else{
        lmin = l1;
        lmax = l2;
    }
    int beg = 0, end = lmin;
    int mid;
    while(beg<=end)
    {
        mid = (beg+end)/2;
        printf("length = %d\n",mid);
        findHash(s1,mid,arr);
        if(searchHash(s2,mid,arr))
        {
            ans = mid;
            beg = mid+1;
        }
        else{
            end = mid-1;
        }
    }
    return ans;
}


int findBiggest(int n,int k,int l)
{
    int arr[k][n][102];
    for(int i=0;i<k;i++)
        for(int j=0;j<n;j++)
            arr[i][j] = 0;
    char s[k][n];
    int len = 0;
    for(int i=0;i<k;i++)
    {
        scanf("%s",s[k]);
    }

}

int main()
{
    int n,k,l;
    scanf("%d %d %d",&n,&k,&l);
    findBiggest(n,k,l);
    return 0;
}