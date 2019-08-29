#include <stdio.h>
#include <string.h>

void replaceSpace(char *str,int length)
    {
        int num=0,sum=0;
        for(int i=0;i<length;i++)
        {
            if (str[i] == ' ') num++;
        }
        for(int i=length-1;i>=0;i--)
        {
            if (str[i] == ' ')
            {
                for(sum;sum>0;sum--)
                {
                    str[i+2*num+sum]=str[i+sum];
	//				printf("%c\n",str[i+sum]);
                }
				num--;
                str[i+2*num] = '%';
                str[i+1+2*num] = '2';
                str[i+2+2*num] = '0';
                sum=0;
            }
            else
            {
                sum++;
            }
        }
}

int main()
{
	char str[100] = "we are champion";
	int len=strlen(str);
	replaceSpace(str,len);
	puts(str);
}
