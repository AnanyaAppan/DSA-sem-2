#include<stdio.h>
#include<stdlib.h>

struct node{
    int data;
    struct node *next;
};

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

int insertEnd(struct node **head, int data)
{
    struct node *temp = (struct node *)malloc(sizeof(struct node));
    if(*head == NULL){
        insertBeg(head,data);
        return 0;
    }
    struct node *temp2 = (struct node *)malloc(sizeof(struct node));
    temp2 = *head;
    while(temp2->next != NULL)
    {
        temp2 = temp2->next;
    }
    temp->next = NULL;
    temp2->next = temp;
    temp->data = data;
    return 0;
}

int printArray(int arr[], int i,int j)
{
    for(int k=i;k<=j;k++) printf("%d ",arr[k]);
    printf("\n");
    return 0;
}

int countSort(int arr[],int n)
{
    int c[1000],b[1000];
    for(int i=0;i<1000;i++) c[i] = 0;
    for(int i=0;i<n;i++) c[arr[i]-1]++;
    for(int i=1;i<1000;i++) c[i] += c[i-1];
    printArray(c,0,n-1);
    for(int i=n-1;i>=0;i--)
    {
        b[c[arr[i]-1]-1] = arr[i];
        c[arr[i]-1] --;
    }
    for(int i=0;i<n;i++) arr[i] = b[i];
    return 0;
}

int bucketSort(int arr[],int n)
{
    struct node* c[10000];
    for(int i=0;i<10000;i++) c[i]=NULL;
    for(int i=0;i<n;i++)
    {
        insertEnd(&c[arr[i]],arr[i]);
    }
    int b[1000];
    int j=0;
    for(int i=0;i<10000;i++)
    {
        if(c[i]!=NULL)
        {
            while(c[i]!=NULL)
            {
                b[j] = c[i]->data;
                c[i] = c[i]->next;
                j++;
            }
        }
    }
    for(int i=0;i<n;i++) arr[i] = b[i];
    return 0;
}

int main()
{
    int n;
    scanf("%d",&n);
    int arr[100];
    for(int i=0;i<n;i++)
    {
        scanf("%d",&arr[i]);
    }
    printf("array before sorting\n");
    printArray(arr,0,n-1);
    bucketSort(arr,n);
    printf("array after sorting\n");
    printArray(arr,0,n-1);
    return 0;
}