#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int counter = 0;
int main(void)
{
  int N, a[100010], b[100010], count, count2;
  
  scanf("%d", &N);
  for(int i = 0; i < N-1; i++)
    scanf("%d%d",&a[i],&b[i]);
  
  
  for(int i = 0; i < N-1; i++)
  {
    count = 0;
    count2 = 0;
    for(int ii = 0; ii < N-1; ii++)
    {
		++counter;
      if(a[i]==a[ii])
        count++;
      else if(a[i]==b[ii])
        count++;
      else
      {
        count2++;
        if(count2==3)
          break;
      }
      if(count == N-1)
      {
        printf("Yes\n");
        return 0;
      }
    }
  }

  for(int i = 0; i < N-1; i++)
  {
    count = 0;
    count2 = 0;
    for(int ii = 0; ii < N-1; ii++)
    {
		++counter;
      if(b[i]==b[ii])
        count++;
      else if(b[i]==a[ii])
        count++;
      else
      {
        count2++;
        if(count2==3)
          break;
      }
    }
    if(count == N-1)
    {
      printf("Yes\n");
      return 0;
    }
  }
  printf("counter:%d\n",counter);
  printf("No\n");
}