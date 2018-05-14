# include <stdio.h>
# include <string.h>
# include <math.h>

# define d 256
# define m 101
int res_a=0,res_b=0;
int max = 1;

void print_array(int arr[], int n)
{
  int i;
  for(i=0; i<n; i++)
    printf("%d ",arr[i]);
  printf("\n");
}

int binary_search(int start, int end, int prefix[], int suffix[],int n,char *str)
{
//  printf("ENTERING FUNCTION\n");
  int left,right,r;
  int x,y,j,p=1;
  int mid_a = (end+start)/2;
  int mid_b = mid_a+1;
  int z,w;
  if(end >= start && mid_a>0 && mid_a<=n)
  {

    int i;
    for(i=0; i <= n-mid_a; i++)
    {
      p=1;
      //printf("Entered for loop\n");
      left = i;
      right = i+mid_a-1;
      r = right - left +1;
      for(j=0; j<r; j++)
        p =((p%m)*(d%m))%m;
      if(left == 0)
        x = 0;
      else
        x = ((prefix[left-1]%m)*(p%m))%m;
      if(n-right-1 == 0)
        y = 0;
      else
        y = ((suffix[n-right-2]%m)*(p%m))%m;

      if((prefix[right]-x+m)%m == (suffix[n-left-1]-y+m)%m)
      {
        for(w=i, z=i+mid_a-1; (z-w)>1 && (z!=w); w++,z-- )
        {
          if(str[w]!=str[z])
            break;
        }
        if(z==w || z-w == 1)
        {
          res_a = left;
          res_b = right;
          max = mid_a;
          break;
       }

      }
    }


    for(i=0; i <= n-mid_b; i++)
    {
      p =1;
    //  printf("Entered for loop 2\n");
      left = i;
      right = i+mid_b-1;
      r = right - left +1;
      for(j=0; j<r; j++)
        p =((p%m)*(d%m))%m;
      if(left == 0)
        x = 0;
      else
        x = ((prefix[left-1]%m)*(p%m))%m;
      if(n-right-1 == 0)
        y = 0;
      else
        y = ((suffix[n-right-2]%m)*(p%m))%m;
      //  printf("lhs = %d rhs = %d\n",prefix[right]-x,suffix[n-left-1]-y );
      if((prefix[right] - x +m)%m == (suffix[n-left-1] - y + m )%m)
      {
        for(w=i, z=i+mid_b-1; (z-w)>1 && (z!=w); w++,z-- )
        {
          if(str[w]!=str[z])
            break;
        }
        if(z==w || z-w == 1)
        {
          res_a = left;
          res_b = right;
          max = mid_b;
          break;
       }

      }
    }
    //printf("Out of for loop\n");
    if(max == mid_a || max == mid_b || mid_a==1)
    {
      //printf("MORE\n");
      binary_search(mid_b+1,end,prefix,suffix,n,str);
    }
    else if(mid_a<n && mid_a>0)
    {
      //printf("LESS\n");
      binary_search(start,mid_a-1,prefix,suffix,n,str);
    }
  }
//  printf("Start index is %d and End index is %d\n",res_a,res_b);
//  printf("Length is %d\n",max);
  return max;
}
int longest_palindrome(char *str)
{
  int len = strlen(str);
  int prefix[len];
  int suffix[len];
  int i;
  int p=0,s=0;
  for(i=0; i<len; i++)
  {
    prefix[i] = (((p%m)*(d%m))%m + (str[i]%m))%m;
    p = prefix[i]%m;
    suffix[i] = (((s%m)*(d%m))%m + (str[len-i-1]%m))%m;
    s = suffix[i]%m;
  }
//  print_array(prefix,len);
//  print_array(suffix,len);
//  printf("Arrays computed!\n");
  return binary_search(0,len,prefix,suffix,len,str);
}


int main()
{
  char str[100001];
  scanf("%s",str);
  printf("%d\n",longest_palindrome(str));
  int i;
  for(i=res_a; i<=res_b; i++)
    printf("%c",str[i]);
  printf("\n");
  return 0;
}
