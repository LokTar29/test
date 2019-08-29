#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<stdbool.h>

char ppp ();
int h[10]={0,1,2,3,4,5,6,7,8,9};


int main()
{
  int a,b,c=0;
  //char p=false;
  while(ppp()==false)
    {
	  srand((unsigned)time(NULL));
      a=rand()%9+1;
	  b=rand()%9+1;
      c=h[a];
	  h[a]=h[b];
	  h[b]=c;
	  printf("%d  %d\n",a,b);
    }
		                 for(int i=1;i<4;i++)
						 {
						   for (int j=1;j<4;j++)
							   printf("%d" ,h[j+3*(i-1)]);
                           printf("\n");
					      }
}

char ppp()
{
   if (h[1]+h[2]+h[3]==h[1]+h[4]+h[7] && h[1]+h[5]+h[9]==h[1]+h[2]+h[3] &&h[1]+h[2]+h[3]==h[3]+h[6]+h[9] && h[1]+h[2]+h[3]==h[2]+h[5]+h[8] && h[1]+h[2]+h[3]==h[7]+h[5]+h[3])
	  return true;
	 else return false;
}
