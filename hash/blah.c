#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

// typedef struct node{
//     int data;
//     struct node *next;
// }node;

int stringhash(char* x, int len)
{
    int p = 100003;
    int result = 0;
    for(int i=0;i<len;i++)
    {
        result = (result%p+((int)x[i]*(int)pow(26,len-i-1))%p)%p;
    }
    return result;
}

// int search(struct node *head,int num)
// {
//     int ans = 0;
//     while(head != NULL)
//     {
//         if(head->data == num)
//         {
//             return ans;
//         }
//         head = head->next;
//         ans++;
//     }
//     return -1;
// }

// int hash(int x)
// {
//     int p = 101513;
//     return x%p;
// }

// int printList(struct node *head)
// {
//     while(head != NULL)
//     {
//         printf("%d\t",head->data);
//         head = head->next;
//     }
//     return 0;
// }

// int insertBeg(struct node **head, int data)
// {
//     struct node *temp = (struct node *)malloc(sizeof(struct node));
//     temp->next = (*head);
//     *head = temp;
//     temp->data = data;
//     return 0;
// }

// int delBeg(struct node **head)
// {
//     if(*head != NULL)
//     {   
//         struct node *temp = (struct node *)malloc(sizeof(struct node));
//         temp = *head;
//         *head = (*head)->next;
//         free(temp);
//         return 0;
//     }
// }

// int delPos(struct node **head, int pos)
// {
//     if(head != NULL)
//     {
//         if(pos == 1)
//         {
//             delBeg(head);
//             return 0;
//         }
//         struct node *temp = (struct node *)malloc(sizeof(struct node));
//         struct node *temp2 = (struct node *)malloc(sizeof(struct node));
//         temp = *head;
//         int cur = 1;
//         while(cur != pos)
//         {
//             temp2 = temp;
//             temp = temp->next;
//             cur++;
//         }
//         temp2->next = temp->next;
//         free(temp);
//         return 0;
//     }
//     return 1;
// }

// int add(int x, node* arr[])
// {
//     int pos = hash(x);
//     insertBeg(&arr[pos],x);
//     return 0;
// }

// int del(int x, node* arr[])
// {
//     int pos1 = hash(x);
//     int pos2 = search(arr[pos1],x);
//     delPos(&arr[pos1],pos2+1);
//     return 0; 
// }

// int HashTableSearch(int x,node* arr[])
// {
//     int pos = hash(x);
//     if(search(arr[pos],x)!=-1) return 1;
//     return 0;
// }

int findHash(char* string, int len, int arr[])
{
    char* firstStr = (char*)malloc(len*sizeof(char));
    int p = 100003;
    for(int i=0;i<len;i++) 
    {
        firstStr[i] = string[i];
    }
    firstStr[len] = '\0';
    int hash = stringhash(firstStr,len);
    printf("hash added = %d\n",hash);
    arr[hash] = 1;
    for(int i=1; i<=strlen(string)-len;i++)
    {
        hash = (hash * 26)%p;
        hash = (hash-((((int)string[i-1])%p)*((int)pow(26,len))%p)%p)%p;
        if(hash<0) hash += p;
        hash = (hash + ((int)string[i+len-1])%p)%p;
        printf("hash added = %d\n",hash);
        arr[hash] = 1;
    }
    return 0;
}

int searchHash(char* string, int len, int arr[])
{
    char* firstStr = (char*)malloc(len*sizeof(char));
    for(int i=0;i<len;i++) 
    {
        firstStr[i] = string[i];
    }
    firstStr[len] = '\0';
    printf("precomputed string = %s\n",firstStr);
    int hash = stringhash(firstStr,len);
    printf("hash formed = %d\n",hash);      
    if(arr[hash]) return 1;
    int p = 100003;
    for(int i=1; i<=strlen(string)-len;i++)
    {
        hash = ((hash)%p*26)%p;
        hash = (hash-(((int)string[i-1])*(int)pow(26,len))%p)%p;
        if(hash<0) hash += p;
        hash = (hash + ((int)string[i+len-1])%p)%p;
        printf("hash formed = %d\n",hash);
        if(arr[hash]) return 1;
    }
    return 0;
}

int longestCommonSubstr(char* s1, char* s2)
{
    int arr[101513];
    for(int i=0;i<101513;i++) arr[i] = 0;
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
    int beg = 0, end = lmin-1;
    int mid;
    while(beg<=end)
    {
        mid = (beg+end)/2;
        printf("the length = %d\n",mid+1);
        findHash(s1,mid+1,arr);
        if(searchHash(s2,mid+1,arr))
        {
            ans = mid;
            beg = mid+1;
        }
        else{
            end = mid-1;
        }
    }
    return ans+1;
}

int main()
{
    printf("enter string 1:");
    char s1[20],s2[20];
    scanf("%s",s1);
    printf("enter string 2:");
    scanf("%s",s2);
    int len = longestCommonSubstr(s1,s2);
    printf("the length of longest common substring = %d\n",len);
    return 0;
}