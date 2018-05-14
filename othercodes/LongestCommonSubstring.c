#include<stdio.h>
#include<string.h>
#include<stdlib.h>
int func( char string1[] , char string2[] , int l1 , int l2 , int l,int left , int right)
{
  int M = l;
  printf("...l is %d \n",l);
  printf("...left is %d and right is %d \n",left,right);


  int d = 256;
  int prime = 10001;
  int arr[prime];
  int z;
  for( z = 0 ; z< prime ; z++)
  {
    arr[z] = -1;
  }


  int T = 0 , P = 0 , h=1;

  int i , j , k ;
  for( i = 0 ; i < l ; i++)
  {
    P = (string1[i] + d*P)%prime;
    T = (string2[i] + d*T)%prime;
    h = (h*d)%prime;
  }
  for( j = 0 ; j<= l1-l ; j++)
  {
    //if( l == 4 && j == 1) printf("..!!..%d \n",P);
    arr[P] = 1;
    P = ( (P*d%prime - h*string1[j]%prime)%prime + string1[j+l]%prime)%prime;
    if( P < 0) P= P+prime;
  }
  int count = 0 ;
  for( k = 0 ; k <= l2-l ; k++)
  {
    if( l == 4 && k == 1) printf("....////....%d \n",T);
    if( arr[T] == 1) {count = 1;break;}
    T = ( (T*d%prime - h*string2[k]%prime)%prime + string2[k+l]%prime)%prime;
    if( T < 0) T = T+prime;
  }
   if( count == 1) {left = l+1;if( left>right) {printf("THE ANSWER IS (fl) ---- %d \n",l);return l;}}
   if( count == 0 ) {right = l-1;if( left > right) {printf("THE ANSWER IS (fr) ---- %d \n",left-1);return left-1;}}
  //if( left>right) {printf("yo\n");printf("................ THE ANSWER IS %d \n",l);return l;}
  // check below line
  if( count == 1) {printf("........yo1 \n");left = l+1 ; M = left ; func( string1 , string2 , l1 , l2 , l + (right-l+1)/2 ,left,right);}
  if ( count == 0 ) {printf("........yo2 \n");right = l-1 ; M = right ;func( string1 , string2 , l1 , l2 , l - (l-left+1)/2 , left , right);}

}
int main()
{
  char string1[] =  { "malayalam"};
  char string2[] =  { "jjhuad"};
  int l1 = strlen(string1);
  int l2 = strlen(string2);
  int l;
  if( l1>l2) l = l2/2;
  else l = l1/2;
  int left = 1;
  int right;
  if( l1>l2) right = l2;
  else right = l1;
  printf("l is %d \n",l);
  if ( l1>l2) printf("%d \n", func(string2 , string1 , l2 , l1 , l,left,right ));
  else printf("length = %d \n",func( string1 , string2 , l1 , l2, l,left,right));
  return 0;
}
