#include<stdio.h>
#include <stdlib.h>
#include <string.h>
int subtract3(int arr[],int n)
{
    if(arr[n-1]>=3) arr[n-1] -= 3;
    else{
        arr[n-1] = arr[n-1]+10 - 3;
        int i=n-2;
        while(arr[i]==0)
        {
            arr[i] = 9;
            i--;
        }
        arr[i]--;
    }
    return 0;
}
int main()
{
    int n = 5,i;
    int ar[5] = {1, 2, 2, 2, 2};
    subtract3(ar, n);
    for (i = 0; i < n; i ++)
        printf ("%d ", ar[i]);
    return 0;
}