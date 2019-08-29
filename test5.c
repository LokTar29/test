#include <stdio.h>
int main()
{
	int index =6;
	for(int i=1;i<10000;i++)
        {
            if (1 == i|2 == i)
            {
                printf("%d ",i);
                index--;
				continue;
            }
            for(int j=2;j<i;i++)
            {
                if (0 == i%j && j !=2|j !=3|j!=5)
                {
                    break;
                }
                if (j == i-1) 
                {
                    printf("%d ",i);
                    index--;
                }
            }
            if (0 == index) 
            {
                break;
            }
        }
}
