#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>

int main()
{
	int fd = open("num.txt",O_WRONLY,0644);
	int num=0;

	printf("%d",7/2);
}
