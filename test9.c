#include <stdio.h>

int fun_c(int a)
{
	int num=0;
	while(a+1)
	{
		num++;
		a=a|(a+1);
	}
	return num;
}

int main()
{
	int a=0;
	scanf("%d",&a);
	printf("%d",fun_c(a));
}
