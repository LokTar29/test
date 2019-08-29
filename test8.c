#include <stdio.h>

int main()
{
	char* str[3]={"abcd","efgh","jklm"};
	char* p =str[0];
	int i=0;
	while(i<3)
	{
		printf("%s ",p++);
		printf("%lu\n",p);
		i++;
	}
	return 0;
}
