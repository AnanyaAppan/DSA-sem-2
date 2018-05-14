#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#define D 10

typedef struct node{
    int data;
    struct node *next;
}node;

int strrev(char* rev,char* s)
{
    int len = strlen(s);
    for(int i = len-1;i>=0;i--) rev[i] = s[len-i-1];
    return 0;
}

int stringhash1(char* x, int len)
{
    int p = 100003;
    int result = 0;
    for(int i=0;i<len;i++)
    {
        result = (result%p+(((int)x[i]-(int)'a'+1)*(int)pow(D,len-i-1))%p)%p;
    }
    return result;
}

int stringhash2(char* x, int len)
{
    int p = 100003;
    int result = 0;
    for(int i=0;i<len;i++)
    {
        result = (result%p+(((int)x[i]-(int)'a'+1)*(int)pow(D,i))%p)%p;
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
    int p = 100003;
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

int searchHashEven(char* string, int len, node* arr[])
{
    printf("len = %d\n",len);
    if(len/2==0) return 1;
    
    printf("%s \n",string);
    char* rev = (char*)malloc((strlen(string))*sizeof(char));
    strrev(rev,string);
    char* firstStrPrefix = (char*)malloc((len/2)*sizeof(char));
    char* firstStrSuffix = (char*)malloc((len/2)*sizeof(char));
    int p = 100003;
    int i,j,k;
    for(i=0,j=len-1,k=0;i<len/2;i++,j--,k++) 
    {
        firstStrPrefix[i] = string[i];
        firstStrSuffix[k] = string[j];
    }
    firstStrPrefix[i] = '\0';
    firstStrSuffix[k] = '\0';
    printf("%s %s\n",firstStrPrefix,firstStrSuffix);
    int hash1 = stringhash1(firstStrPrefix,len/2);
    int hash2 = stringhash1(firstStrSuffix,len/2);
    printf("hash1 = %d hash2 = %d\n",hash1,hash2);
    if(hash1==hash2) return 1;
    for(int i=1,j=strlen(string)-len/2-2; j>=len/2-1 ;i++,j--)
    {
        printf("for first...+ %c - %c\n",string[i+len/2-1],string[i-1]);
        printf("for second....+ %c - %c\n",rev[j-len/2+1],rev[j+1]);
        hash1 = ((((hash1 - (string[i-1]*(int)pow(D,len/2-1))%p + p)%p)*D)%p + string[i+len/2-1])%p;
        hash2 = ((((hash2 - (rev[j]*(int)pow(D,len/2-1))%p + p)%p * D)%p) + rev[j-len/2+1]%p);
        if(hash1==hash2)  return 1;
        printf("hash1 = %d hash2 = %d\n",hash1,hash2);
    }
    
    return 0;
}


int searchHashOdd(char* string, int len, node* arr[])
{
    printf("len = %d\n",len);
    if(len/2==0) return 1;
    printf("%s \n",string);
    char* rev = (char*)malloc((strlen(string))*sizeof(char));
    strrev(rev,string);
    char* firstStrPrefix = (char*)malloc((len/2)*sizeof(char));
    char* firstStrSuffix = (char*)malloc((len/2)*sizeof(char));
    int p = 100003;
    int i,j,k;
    for(i=0,j=len-1,k=0;i<len/2;i++,j--,k++) 
    {
        firstStrPrefix[i] = string[i];
        firstStrSuffix[k] = string[j];
    }
    firstStrPrefix[i] = '\0';
    firstStrSuffix[k] = '\0';
    printf("%s %s\n",firstStrPrefix,firstStrSuffix);
    int hash1 = stringhash1(firstStrPrefix,len/2);
    int hash2 = stringhash1(firstStrSuffix,len/2);
    printf("hash1 = %d hash2 = %d\n",hash1,hash2);
    if(hash1==hash2) return 1;
    for(int i=1,j=strlen(string)-len/2-3; j>=len/2-1;i++,j--)
    {
        printf("for first...+ %c - %c\n",string[i+len/2-1],string[i-1]);
        printf("for second....+ %c - %c\n",rev[j-len/2+1],rev[j+1]);
        hash1 = ((((hash1 - (string[i-1]*(int)pow(D,len/2-1))%p + p)%p)*D)%p + string[i+len/2-1])%p;
        hash2 = ((((hash2 - (rev[j]*(int)pow(D,len/2-1))%p + p)%p * D)%p) + rev[j-len/2+1]%p);
        if(hash1==hash2) return 1;
        printf("hash1 = %d hash2 = %d\n",hash1,hash2);
    }
    return 0;
}

int longestPal(char* s1)
{
    node* arr[101513];
    int l1 = strlen(s1);
    int ans = 1;
    char* substr = (char*)malloc(l1*sizeof(char));
    int beg = 0, end = l1;
    int mid;
    while(beg<=end)
    {
        mid = (beg+end)/2;
        if(mid%2 == 0)
        {
            if(searchHashEven(s1,mid,arr))
            {
                ans = mid;
                beg = mid+1;
            }
            else
            {
                if(searchHashOdd(s1,mid+1,arr))
                {
                    ans = mid+1;
                    beg = mid+2;
                }
                else{
                    end = mid-1;
                }
            }
        }
        else{

            if(searchHashOdd(s1,mid,arr))
            {
                ans = mid;
                beg = mid+1;
            }
            else 
            {
                if(searchHashEven(s1,mid+1,arr))
                {
                    ans = mid+1;
                    beg = mid+2;
                }
                else{
                    end = mid-1;
                }
            }
        }
    }
    return ans;
}

int main()
{
    printf("enter string 1:");
    char s1[20];
    scanf("%s",s1);
    int len = longestPal(s1);
    printf("the length of longest common palindrome = %d\n",len);
    return 0;
}